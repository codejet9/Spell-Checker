# Spell Checker Using Dynamic Programming

- This program takes a string(a sentence or paragraph) as input in the terminal and corrects all the misspelled word.
- It breaks the sentence/paragraph into individual words and analyzes them.
- A dictionary of around 200K words along with frequency of usage of each word is collected and added to a textfile.
- All the words in dictionary along with their frequencies are hashed into an unordered map.
- During analysis of a word, the program first checks if the word is present in the map. If it is, then it returns the word as it is.
- If not then it calculates the edit distance/Levenshtein distance between the current word and each word in dictionary using a Bottom-Up/Iterative Dynamic Programming method. Replace, Erase and Add character are taken as the three possible operations on the string.
- It takes those words which have lowest Levenshtein distance. Because it is assumed that these are the nearest words which the author meant to type.
- Among the words with lowest edit distance, the word with highest frequency of usage in english is returned. It is assumed that the word with highest usage frequency is the nearest correct word.
- This may not give the exact correct word for a misspelled word since many words can be possible. But it gives the most probable word.
- 
![spellcheck_picture](https://user-images.githubusercontent.com/108319876/176109101-942d823f-d95f-4c4a-8cd5-c8c517782002.png)
