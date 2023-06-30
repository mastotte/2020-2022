INSTRUCTIONS

*ON SIGN-IN: Check if player's tag matches tag in database "members.txt".
If it doesn't match, assume the player switched tags with someone. Change tags manually.

********Example********
"members.txt" reads:
-------------
Paul McBeth,1
Howard Tan,2
-------------

Howard Tan signs in, and puts the #1 tag in the pool.

"members.txt" should be changed to:
-------------
Paul McBeth,2
Howard Tan,1
-------------
************************

Also, if a new player signs up, add their name and new tag number to members.txt.

*AFTER ROUND: Go to the UDisc results, and click "Export to CSV". It will download the scores.
Go to your downloads, right click it->open with->notepad. Copy the contents of the file to "players.txt".

Double click "bagtags.exe".