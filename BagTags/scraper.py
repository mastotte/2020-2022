import requests
from bs4 import BeautifulSoup
import json
import re
from datetime import datetime
import pandas as pd
import time
import logging
import os

# Set up logging
logging.basicConfig(
    level=logging.DEBUG,
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler("udisc_scraper.log"),
        logging.StreamHandler()
    ]
)

def get_latest_tournament_url(league_url):
    """
    Get the URL for the most recent tournament from the league page.
    
    Args:
        league_url (str): URL of the league page (e.g., https://udisc.com/leagues/oak-grove-disc-golf-club-kbP0WC)
    
    Returns:
        str: URL for the most recent tournament's leaderboard
    """
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36",
        "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
        "Accept-Language": "en-US,en;q=0.5",
        "Accept-Encoding": "gzip, deflate, br",
        "Connection": "keep-alive",
        "Upgrade-Insecure-Requests": "1",
        "Cache-Control": "max-age=0"
    }
    
    try:
        logging.info(f"Fetching league page: {league_url}")
        response = requests.get(league_url, headers=headers)
        response.raise_for_status()
        
        # Save the HTML for debugging
        with open("league_page.html", "w", encoding="utf-8") as f:
            f.write(response.text)
        logging.info("Saved league page HTML to league_page.html")
        
        soup = BeautifulSoup(response.text, 'html.parser')
        
        # Look for all script tags with application/json
        script_tags = soup.find_all('script', type='application/json')
        logging.info(f"Found {len(script_tags)} script tags with application/json")
        
        # Find the most recent event
        most_recent_date = None
        most_recent_event_id = None
        
        for i, script in enumerate(script_tags):
            try:
                data = json.loads(script.string)
                
                # Save each script's JSON for debugging
                with open(f"script_{i}.json", "w", encoding="utf-8") as f:
                    json.dump(data, f, indent=2)
                
                # Look for events data in the JSON
                if 'props' in data and 'pageProps' in data['props']:
                    logging.info(f"Found pageProps in script {i}")
                    
                    if 'league' in data['props']['pageProps'] and 'events' in data['props']['pageProps']['league']:
                        events = data['props']['pageProps']['league']['events']
                        logging.info("Found league events data")
                        
                        # Check both past and upcoming events
                        if 'past' in events and isinstance(events['past'], list):
                            past_events = events['past']
                            logging.info(f"Found {len(past_events)} past events")
                            for event in past_events:
                                if 'startDate' in event and 'id' in event:
                                    event_date = datetime.fromisoformat(event['startDate'].replace('Z', '+00:00'))
                                    logging.info(f"Past event: {event.get('name', 'Unknown')} on {event_date} with ID {event['id']}")
                                    if most_recent_date is None or event_date > most_recent_date:
                                        most_recent_date = event_date
                                        most_recent_event_id = event['id']
                                        logging.info(f"New most recent event: {event.get('name', 'Unknown')} on {event_date}")
                        
                        # Also check upcoming events that might have already started
                        if 'upcoming' in events and isinstance(events['upcoming'], list):
                            upcoming_events = events['upcoming']
                            logging.info(f"Found {len(upcoming_events)} upcoming events")
                            for event in upcoming_events:
                                if 'startDate' in event and 'id' in event:
                                    event_date = datetime.fromisoformat(event['startDate'].replace('Z', '+00:00'))
                                    logging.info(f"Upcoming event: {event.get('name', 'Unknown')} on {event_date} with ID {event['id']}")
                                    now = datetime.now()
                                    logging.info(f"Current time: {now}")
                                    if event_date <= now and (most_recent_date is None or event_date > most_recent_date):
                                        most_recent_date = event_date
                                        most_recent_event_id = event['id']
                                        logging.info(f"New most recent event: {event.get('name', 'Unknown')} on {event_date}")
                        
                        break  # Found the events data, no need to check other scripts
            except Exception as e:
                logging.error(f"Error processing script {i}: {e}")
                continue
        
        if most_recent_event_id:
            # Construct the leaderboard URL for the most recent event
            url = f"https://udisc.com/events/{most_recent_event_id}/leaderboard?round=1&view=scores"
            logging.info(f"Found most recent event URL: {url}")
            return url
        else:
            logging.warning("No event ID found in JSON. Falling back to HTML parsing.")
            # If no specific event found, look for <a> tags with event URLs
            event_links = soup.select('a[href*="/events/"]')
            logging.info(f"Found {len(event_links)} event links in HTML")
            
            most_recent_link = None
            
            # Extract event IDs from hrefs
            for link in event_links:
                href = link.get('href', '')
                logging.info(f"Found link: {href}")
                if '/events/' in href and '/leaderboard' not in href:
                    event_id_match = re.search(r'/events/([^/]+)', href)
                    if event_id_match:
                        event_id = event_id_match.group(1)
                        logging.info(f"Extracted event ID: {event_id}")
                        if most_recent_link is None:
                            most_recent_link = f"https://udisc.com/events/{event_id}/leaderboard?round=1&view=scores"
                            logging.info(f"Using first found event URL: {most_recent_link}")
            
            # If all else fails, try direct URLs from your examples
            if most_recent_link is None:
                logging.warning("No links found. Trying example URLs.")
                example_urls = [
                    "https://udisc.com/events/oak-grove-disc-golf-club-weekly-1p-check-in-2p-shotgun-start-new-spring-hours-nE72w8/leaderboard?round=1&view=scores",
                    "https://udisc.com/events/oak-grove-disc-golf-club-weekly-1p-check-in-2p-shotgun-start-new-spring-hours-0sFQGv/leaderboard?round=1&view=scores"
                ]
                
                # Try to access each URL and use the first one that works
                for url in example_urls:
                    try:
                        test_response = requests.head(url, headers=headers, timeout=5)
                        if test_response.status_code == 200:
                            logging.info(f"Example URL {url} is accessible")
                            most_recent_link = url
                            break
                    except:
                        logging.warning(f"Example URL {url} is not accessible")
            
            return most_recent_link
            
    except Exception as e:
        logging.error(f"Error getting latest tournament URL: {e}", exc_info=True)
        return None

def scrape_tournament_results(url):
    """
    Scrape tournament results from the given URL.
    
    Args:
        url (str): URL of the tournament leaderboard
    
    Returns:
        pd.DataFrame: DataFrame containing the tournament results
    """
    if not url:
        logging.error("No URL provided for scraping")
        return None
    
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36",
        "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
        "Accept-Language": "en-US,en;q=0.5",
        "Accept-Encoding": "gzip, deflate, br",
        "Connection": "keep-alive",
        "Upgrade-Insecure-Requests": "1",
        "Cache-Control": "max-age=0"
    }
    
    try:
        logging.info(f"Scraping tournament results from: {url}")
        response = requests.get(url, headers=headers, timeout=30)
        response.raise_for_status()
        
        # Save the HTML for debugging
        with open("tournament_page.html", "w", encoding="utf-8") as f:
            f.write(response.text)
        logging.info("Saved tournament page HTML to tournament_page.html")
        
        soup = BeautifulSoup(response.text, 'html.parser')
        
        # Try to verify if the page is a leaderboard
        if "leaderboard" not in response.text.lower() and "scores" not in response.text.lower():
            logging.warning("Page might not be a leaderboard - keywords not found")
        
        # Tournament title
        tournament_title = None
        title_element = soup.select_one('h1')
        if title_element:
            tournament_title = title_element.text.strip()
            logging.info(f"Found tournament title: {tournament_title}")
        else:
            logging.warning("Title element (h1) not found")
        
        # Date of tournament
        tournament_date = None
        date_element = soup.select_one('time')
        if date_element:
            date_text = date_element.text.strip()
            logging.info(f"Found date element text: {date_text}")
            try:
                # Try to parse the date from the text
                date_match = re.search(r'(\w+ \d+, \d{4})', date_text)
                if date_match:
                    tournament_date = date_match.group(1)
                    logging.info(f"Parsed tournament date: {tournament_date}")
            except Exception as e:
                logging.error(f"Error parsing tournament date: {e}")
        else:
            logging.warning("Date element (time) not found")
        
        # Look for script tags with JSON data
        script_tags = soup.find_all('script', type='application/json')
        logging.info(f"Found {len(script_tags)} script tags with application/json")
        
        # Try using a more direct selector for player data
        player_rows = soup.select('table tr')
        if player_rows and len(player_rows) > 1:  # More than just header row
            logging.info(f"Found {len(player_rows)} player rows in HTML table")
            
            # Try to extract data directly from HTML
            results = []
            
            for row in player_rows[1:]:  # Skip header row
                cells = row.select('td')
                if len(cells) >= 4:  # Minimum cells for position, name, total, par
                    player_data = {
                        'Position': cells[0].text.strip() if cells[0].text.strip() else '',
                        'Name': cells[1].text.strip() if len(cells) > 1 else '',
                        'Total': cells[2].text.strip() if len(cells) > 2 else '',
                        'Par': cells[3].text.strip() if len(cells) > 3 else ''
                    }
                    
                    # Try to get hole scores
                    for i, cell in enumerate(cells[4:]):
                        player_data[f'Hole {i+1}'] = cell.text.strip()
                    
                    results.append(player_data)
            
            if results:
                logging.info(f"Successfully extracted {len(results)} players from HTML table")
                df = pd.DataFrame(results)
                
                # Add tournament info
                if tournament_title:
                    df['Tournament'] = tournament_title
                if tournament_date:
                    df['Date'] = tournament_date
                
                return df
        
        # If HTML table approach failed, try JSON
        for i, script in enumerate(script_tags):
            try:
                data = json.loads(script.string)
                
                # Save each script's JSON for debugging
                with open(f"tournament_script_{i}.json", "w", encoding="utf-8") as f:
                    json.dump(data, f, indent=2)
                
                if 'props' in data and 'pageProps' in data['props']:
                    page_props = data['props']['pageProps']
                    logging.info(f"Found pageProps in script {i}")
                    
                    # Get tournament information if not already extracted
                    if tournament_title is None and 'event' in page_props and 'name' in page_props['event']:
                        tournament_title = page_props['event']['name']
                        logging.info(f"Found tournament title from JSON: {tournament_title}")
                    
                    if tournament_date is None and 'event' in page_props and 'startDate' in page_props['event']:
                        try:
                            date_obj = datetime.fromisoformat(page_props['event']['startDate'].replace('Z', '+00:00'))
                            tournament_date = date_obj.strftime('%B %d, %Y')
                            logging.info(f"Found tournament date from JSON: {tournament_date}")
                        except Exception as e:
                            logging.error(f"Error parsing date from JSON: {e}")
                    
                    # Extract leaderboard data
                    if 'leaderboard' in page_props:
                        logging.info("Found leaderboard property in pageProps")
                        leaderboard = page_props['leaderboard']
                        
                        if isinstance(leaderboard, list) and leaderboard:
                            logging.info(f"Leaderboard contains {len(leaderboard)} players")
                            
                            results = []
                            for player in leaderboard:
                                player_data = {
                                    'Position': player.get('position', ''),
                                    'Name': player.get('name', ''),
                                    'Total': player.get('total', ''),
                                    'Par': player.get('relativeToPar', '')
                                }
                                
                                # Log player info for debugging
                                logging.info(f"Player: {player.get('name', 'Unknown')} - Pos: {player.get('position', 'Unknown')} - Total: {player.get('total', 'Unknown')} - Par: {player.get('relativeToPar', 'Unknown')}")
                                
                                # Add scores for each hole if available
                                if 'scores' in player and isinstance(player['scores'], list):
                                    for i, score in enumerate(player['scores']):
                                        player_data[f'Hole {i+1}'] = score
                                
                                results.append(player_data)
                            
                            df = pd.DataFrame(results)
                            
                            # Add tournament info to the dataframe
                            if tournament_title:
                                df['Tournament'] = tournament_title
                            if tournament_date:
                                df['Date'] = tournament_date
                            
                            logging.info(f"Successfully scraped data for {tournament_title} on {tournament_date}")
                            return df
                        else:
                            logging.warning("Leaderboard is not a list or is empty")
                    else:
                        # Check if there's any other relevant data in the page_props
                        logging.info(f"Keys in pageProps: {page_props.keys()}")
            except Exception as e:
                logging.error(f"Error processing script {i}: {e}", exc_info=True)
                continue
        
        # Try an alternative approach - sometimes the data is in window.__NEXT_DATA__
        next_data_script = soup.find('script', id='__NEXT_DATA__')
        if next_data_script:
            logging.info("Found __NEXT_DATA__ script, trying to extract data")
            try:
                next_data = json.loads(next_data_script.string)
                
                # Save for debugging
                with open("next_data.json", "w", encoding="utf-8") as f:
                    json.dump(next_data, f, indent=2)
                
                # Try to navigate to the leaderboard data
                if 'props' in next_data and 'pageProps' in next_data['props']:
                    props = next_data['props']['pageProps']
                    
                    # Various paths to check for leaderboard data
                    paths_to_check = [
                        ['leaderboard'],
                        ['event', 'leaderboard'],
                        ['data', 'leaderboard'],
                        ['initialState', 'leaderboard'],
                        ['initialState', 'event', 'leaderboard']
                    ]
                    
                    for path in paths_to_check:
                        data = props
                        for key in path:
                            if key in data:
                                data = data[key]
                            else:
                                data = None
                                break
                        
                        if data and isinstance(data, list):
                            logging.info(f"Found leaderboard data using path {path}")
                            # Process similar to above
                            results = []
                            for player in data:
                                if isinstance(player, dict):
                                    player_data = {
                                        'Position': player.get('position', ''),
                                        'Name': player.get('name', ''),
                                        'Total': player.get('total', ''),
                                        'Par': player.get('relativeToPar', '')
                                    }
                                    
                                    # Add scores for each hole if available
                                    if 'scores' in player and isinstance(player['scores'], list):
                                        for i, score in enumerate(player['scores']):
                                            player_data[f'Hole {i+1}'] = score
                                    
                                    results.append(player_data)
                            
                            if results:
                                df = pd.DataFrame(results)
                                
                                # Add tournament info
                                if tournament_title:
                                    df['Tournament'] = tournament_title
                                if tournament_date:
                                    df['Date'] = tournament_date
                                
                                logging.info(f"Successfully scraped data via __NEXT_DATA__")
                                return df
            except Exception as e:
                logging.error(f"Error processing __NEXT_DATA__: {e}", exc_info=True)
        
        logging.error("Could not find leaderboard data in the page.")
        return None
        
    except Exception as e:
        logging.error(f"Error scraping tournament results: {e}", exc_info=True)
        return None

def try_selenium_approach(url):
    """
    Alternative approach using Selenium for JavaScript-rendered content.
    
    Args:
        url (str): URL of the tournament leaderboard
    
    Returns:
        pd.DataFrame: DataFrame containing the tournament results
    """
    try:
        import importlib.util
        
        # Check if selenium is installed
        selenium_installed = importlib.util.find_spec("selenium") is not None
        if not selenium_installed:
            logging.error("Selenium is not installed. To install: pip install selenium")
            return None
        
        from selenium import webdriver
        from selenium.webdriver.chrome.service import Service
        from selenium.webdriver.chrome.options import Options
        from selenium.webdriver.common.by import By
        from selenium.webdriver.support.ui import WebDriverWait
        from selenium.webdriver.support import expected_conditions as EC
        
        logging.info(f"Attempting to scrape with Selenium: {url}")
        
        # Set up Chrome options
        chrome_options = Options()
        chrome_options.add_argument("--headless")  # Run in headless mode
        chrome_options.add_argument("--no-sandbox")
        chrome_options.add_argument("--disable-dev-shm-usage")
        chrome_options.add_argument("--disable-gpu")
        chrome_options.add_argument("--window-size=1920,1080")
        
        # Initialize the driver
        driver = webdriver.Chrome(options=chrome_options)
        
        try:
            driver.get(url)
            logging.info("Page loaded with Selenium")
            
            # Wait for content to load (adjust timeout as needed)
            WebDriverWait(driver, 10).until(
                EC.presence_of_element_located((By.TAG_NAME, "table"))
            )
            
            # Save the page source for debugging
            with open("selenium_page.html", "w", encoding="utf-8") as f:
                f.write(driver.page_source)
            logging.info("Saved Selenium page HTML to selenium_page.html")
            
            # Extract tournament info
            tournament_title = None
            try:
                title_element = driver.find_element(By.TAG_NAME, "h1")
                if title_element:
                    tournament_title = title_element.text.strip()
                    logging.info(f"Found tournament title with Selenium: {tournament_title}")
            except:
                logging.warning("Could not find title element with Selenium")
            
            # Extract date
            tournament_date = None
            try:
                date_element = driver.find_element(By.TAG_NAME, "time")
                if date_element:
                    date_text = date_element.text.strip()
                    date_match = re.search(r'(\w+ \d+, \d{4})', date_text)
                    if date_match:
                        tournament_date = date_match.group(1)
                        logging.info(f"Found tournament date with Selenium: {tournament_date}")
            except:
                logging.warning("Could not find date element with Selenium")
            
            # Extract table data
            results = []
            try:
                table = driver.find_element(By.TAG_NAME, "table")
                rows = table.find_elements(By.TAG_NAME, "tr")
                
                # Skip header row
                for row in rows[1:]:
                    cells = row.find_elements(By.TAG_NAME, "td")
                    if len(cells) >= 4:
                        player_data = {
                            'Position': cells[0].text.strip() if cells[0].text.strip() else '',
                            'Name': cells[1].text.strip() if len(cells) > 1 else '',
                            'Total': cells[2].text.strip() if len(cells) > 2 else '',
                            'Par': cells[3].text.strip() if len(cells) > 3 else ''
                        }
                        
                        # Try to get hole scores
                        for i, cell in enumerate(cells[4:]):
                            player_data[f'Hole {i+1}'] = cell.text.strip()
                        
                        results.append(player_data)
                
                if results:
                    df = pd.DataFrame(results)
                    
                    # Add tournament info
                    if tournament_title:
                        df['Tournament'] = tournament_title
                    if tournament_date:
                        df['Date'] = tournament_date
                    
                    logging.info(f"Successfully scraped data with Selenium")
                    return df
                else:
                    logging.warning("No results found with Selenium table extraction")
            except Exception as e:
                logging.error(f"Error extracting table with Selenium: {e}")
            
            # If table extraction failed, try to get JSON data from the page
            try:
                # Execute JavaScript to get the __NEXT_DATA__ content
                next_data = driver.execute_script("return JSON.parse(document.getElementById('__NEXT_DATA__').textContent);")
                
                # Save for debugging
                with open("selenium_next_data.json", "w", encoding="utf-8") as f:
                    json.dump(next_data, f, indent=2)
                
                # Process the JSON similar to the non-Selenium approach
                if 'props' in next_data and 'pageProps' in next_data['props']:
                    props = next_data['props']['pageProps']
                    
                    # Various paths to check for leaderboard data
                    paths_to_check = [
                        ['leaderboard'],
                        ['event', 'leaderboard'],
                        ['data', 'leaderboard'],
                        ['initialState', 'leaderboard'],
                        ['initialState', 'event', 'leaderboard']
                    ]
                    
                    for path in paths_to_check:
                        data = props
                        for key in path:
                            if key in data:
                                data = data[key]
                            else:
                                data = None
                                break
                        
                        if data and isinstance(data, list):
                            logging.info(f"Found leaderboard data in Selenium using path {path}")
                            results = []
                            for player in data:
                                if isinstance(player, dict):
                                    player_data = {
                                        'Position': player.get('position', ''),
                                        'Name': player.get('name', ''),
                                        'Total': player.get('total', ''),
                                        'Par': player.get('relativeToPar', '')
                                    }
                                    
                                    # Add scores for each hole if available
                                    if 'scores' in player and isinstance(player['scores'], list):
                                        for i, score in enumerate(player['scores']):
                                            player_data[f'Hole {i+1}'] = score
                                    
                                    results.append(player_data)
                            
                            if results:
                                df = pd.DataFrame(results)
                                
                                # Add tournament info
                                if tournament_title:
                                    df['Tournament'] = tournament_title
                                if tournament_date:
                                    df['Date'] = tournament_date
                                
                                logging.info(f"Successfully scraped data with Selenium via JSON")
                                return df
            except Exception as e:
                logging.error(f"Error extracting JSON with Selenium: {e}")
            
            logging.error("Could not find leaderboard data with Selenium")
            return None
        
        finally:
            # Always close the driver
            driver.quit()
    
    except Exception as e:
        logging.error(f"Error in Selenium approach: {e}", exc_info=True)
        return None

def save_results_to_csv(df, filename=None):
    """
    Save tournament results to a CSV file.
    
    Args:
        df (pd.DataFrame): DataFrame containing tournament results
        filename (str, optional): Name of the CSV file. If None, a name will be generated.
    
    Returns:
        str: Path to the saved CSV file
    """
    if df is None or df.empty:
        logging.error("No data to save")
        return None
    
    # Create output directory if it doesn't exist
    output_dir = "tournament_results"
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    
    # Generate filename if not provided
    if filename is None:
        tournament_name = df['Tournament'].iloc[0] if 'Tournament' in df.columns and not df['Tournament'].empty else "unknown_tournament"
        tournament_date = df['Date'].iloc[0] if 'Date' in df.columns and not df['Date'].empty else datetime.now().strftime('%Y-%m-%d')
        
        # Clean the tournament name for use in filename
        tournament_name = re.sub(r'[^\w\s-]', '', tournament_name).strip().replace(' ', '_')
        tournament_date = re.sub(r'[^\w\s-]', '', tournament_date).strip().replace(' ', '_')
        
        filename = f"{tournament_name}_{tournament_date}.csv"
    
    # Ensure the filename has .csv extension
    if not filename.lower().endswith('.csv'):
        filename += '.csv'
    
    # Full path to the output file
    output_path = os.path.join(output_dir, filename)
    
    # Save to CSV
    try:
        df.to_csv(output_path, index=False)
        logging.info(f"Results saved to {output_path}")
        return output_path
    except Exception as e:
        logging.error(f"Error saving results to CSV: {e}")
        return None

def main():
    """
    Main function to run the UDisc tournament scraper.
    """
    # League URL to scrape (can be changed or passed as a command line argument)
    league_url = "https://udisc.com/leagues/oak-grove-disc-golf-club-kbP0WC"
    
    # Get the latest tournament URL
    logging.info(f"Starting scraper for league: {league_url}")
    tournament_url = get_latest_tournament_url(league_url)
    
    if not tournament_url:
        logging.error("Failed to get latest tournament URL. Exiting.")
        return
    
    logging.info(f"Latest tournament URL: {tournament_url}")
    
    # Try to scrape with regular approach first
    results_df = scrape_tournament_results(tournament_url)
    
    # If regular approach fails, try Selenium
    if results_df is None or results_df.empty:
        logging.info("Regular scraping approach failed. Trying Selenium approach.")
        results_df = try_selenium_approach(tournament_url)
    
    # Save results if we got any
    if results_df is not None and not results_df.empty:
        output_path = save_results_to_csv(results_df)
        if output_path:
            logging.info(f"Scraping completed successfully. Results saved to {output_path}")
            
            # Display some summary stats
            print(f"\nScraping completed successfully!")
            print(f"Tournament: {results_df['Tournament'].iloc[0] if 'Tournament' in results_df.columns else 'Unknown'}")
            print(f"Date: {results_df['Date'].iloc[0] if 'Date' in results_df.columns else 'Unknown'}")
            print(f"Number of players: {len(results_df)}")
            print(f"Results saved to: {output_path}")
        else:
            logging.error("Failed to save results")
    else:
        logging.error("Failed to scrape tournament results")

if __name__ == "__main__":
    main()