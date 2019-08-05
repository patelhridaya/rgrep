# rgrep
grep is a UNIX utility that is used to parse or search through strings for a particular pattern. The
strings can be either put in through the console or in text files. It is a very convenient way to look
for basic patterns or ones with wildcards. It is fairly complicated to support the full character set
that grep is capable of. I implemented a restritive grep for a school project. 




It is restrictive with a set of wildcard characters that can be within the pattern (the search term): 

. (period) Matches any character.
+ (plus) The preceding character will appear one or more times
? (question) The preceding character may or may not appear in the line
\ (backslash) "Escapes" the following character, nullifying any special characteristics
