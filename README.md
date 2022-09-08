# Personality-Quiz
Ever wanted to make your own personality quiz? Now you can!

This application is just a simple personality quizzer, asking you questions from a bucket of random ones.
## Makefile
The makefile is broken (I think?):
```
build:
	rm -f program.exe
	g++ -g -std=c++11 -Wall main.cpp -o program.exe
	
run:
	./program.exe
  ```
  ## How use??
  Anyways there's no people file, you have to make that yourself!
  Open up any text editor, and create your own objects and their characteristics. When you're done, save them as .people file.
  
  A single character should be on it's own line to differentiate characters
  Here's the general template to help you out
  ```
  [char name]. O:[number] C:[number] E:[number] A:[number] N:[number] <- newline
  ```
  Here's my own example to start (Using Lost Ark classes)!
  ```
  Sorceress. O:9 C:6 E:-6 A:-7 N:-4
Bard. A:4 E:6 C:3 O:3 N:-1
Berserker. O:0 C:-4 E:6 A:0 N:6
Paladin. O:5 C:0 E:4 A:9 N:2
Gunlancer. O:-3 C:8 E:7 A:9 N:-3
Deathblade. E:-7 O:-4 C:2 A:-6 N:-4
Shadow Hunter. O:2 C:2 E:-4 A:-5 N:0
Scrapper. O:0 C:-4 E:7 A:0 N:2
Soulfist. O:4 C:0 E:4 A:2 N:-3
Striker. O:7 C:3 E:-4 A:0 N:2
Wardancer. O:0 C:9 E:-5 A:0 N:0
Gunslinger. O:7 C:2 E:3 A:2 N:-3
Artillerist. O:-4 C:9 E:0 A:-1 N:-3
Deadeye. O:5 C:-4 E:4 A:-2 N:-8
Sharpshooter. O:-1 C:2 E:-3 A:0 N:0
Sorceress. O:9 C:6 E:-6 A:-7 N:-4
Bard. A:4 E:6 C:3 O:3 N:-1
Berserker. O:0 C:-4 E:6 A:0 N:6
Paladin. O:5 C:0 E:4 A:9 N:2
Gunlancer. O:-3 C:8 E:7 A:9 N:-3
Deathblade. E:-7 O:-4 C:2 A:-6 N:-4
Shadow Hunter. O:2 C:2 E:-4 A:-5 N:0
Scrapper. O:0 C:-4 E:7 A:0 N:2
Soulfist. O:4 C:0 E:4 A:2 N:-3
Striker. O:7 C:3 E:-4 A:0 N:2
Wardancer. O:0 C:9 E:-5 A:0 N:0
Gunslinger. O:7 C:2 E:3 A:2 N:-3
Artillerist. O:-4 C:9 E:0 A:-1 N:-3
Deadeye. O:5 C:-4 E:4 A:-2 N:-8
Sharpshooter. O:-1 C:2 E:-3 A:0 N:0
```
  ## Final Notes:
  * You can omit any ocean characteristic, the app only needs one to read!
  * The more questions you answer, the better the app gets are guessing your personality!
  * <a href ="https://en.wikipedia.org/wiki/Big_Five_personality_traits"> The app uses OCEAN characteristics to distinguish your personality, read up on it if you're not sure what that is! </a>
