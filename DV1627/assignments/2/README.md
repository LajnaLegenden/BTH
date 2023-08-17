# Inlämningsuppgift 2, 'N i rad'

## Snabblänkar till mallar och inlämningssidor

- **Kodmall:**
- **Tillfälle 1:**
- **Tillfälle 2:**
- **Tillfälle 3:**

## Innehåll

- Syfte
- Uppgift
- Kriterier
- Komma igång
- Minnesläckor

## Syfte

Denna uppgift ska examinera dig på:

- Förståelse för klasser
- Hantering av dynamiskt allokerat minne

> Detta är en individuell examination. All kod du lämnar in ska vara skriven av dig och enbart dig, med undantag för den kod som följer med i uppgiftsmallen. Det kommer att utföras en plagieringskontroll på inlämnad kod. Var noga att inte dela din egen kod med andra personer då båda era inlämningar kommer flaggas som plagiat.

## Uppgift

I denna uppgift ska du implementera spelet 4-i-rad (connect four), men för en *godtyckligt stor spelplan* samt *godtyckligt antal pjäser i rad för att vinna*. Ditt program kan exempelvis hantera en 7x6 stor spelplan med 4 pjäser i rad för att vinna (standard), men även ha möjlighet för exempelvis en 100x200 stor spelplan med 43 pjäser i rad för att vinna. Vi kallar detta *N-i-rad*.

Du är given en påbörjad klass som du ska skriva klart. Klassens definition finns i en given headerfil (`.hpp`) och dess medlemsfunktioner finns definierade i en given källfil (`.cpp`).

**Obs! Denna uppgift kräver bara att du färdigställer den givna klassen `ConnectN` (se nedan), det finns inget krav att du implementerar ett gränssnitt för att få godkänt. Det är helt ok att skriva ett eget gränssnitt och ska då göras i filen `main.cpp`; din klass i sig får inte göra några egna utskrifter.**

## Kriterier

För betyget G ska följande kriterier vara uppfyllda:

<!-- - `application` ska kompilera på CodeGrade
	- `application` är en exekverbar fil som byggs av källfilerna:
		- `main.cpp`
		- `ConnectN.cpp` -->
- Spelbrädet ska lagras i en *dynamiskt allorekad tvådimensionell array*
	- Kan även tänkas som en array av arrayer.
	- Detta skrivs i kod som `Colors**` och existerar redan som medlemsvariabel i klassen `ConnectN`.
- Ingen form av behållare från standardbiblioteket får användas, exempelvis `std::vector`, `std::linked_list`, `std::map` etc.
- `auto-tests` ska kompileras på CodeGrade med källfilerna:
	- `test-main.cpp`
	- `ConnectN.cpp`
	- `Visualizer.cpp`
- Alla tester i `auto-tests` ska passera utan att minnesläckor uppstår på CodeGrade.

## Komma igång

Ladda ner och packa upp kodmallen som kan hittas högst upp på denna sida. I projektmappen kan du finna följande mappar och filer:

- `include/`
	- `ConnectN.hpp` <- Du ska modifiera och skicka in denna fil
	- `Visualizer.hpp`
- `src/`
	- `ConnectN.cpp` <- Du ska modifiera och skicka in denna fil
	- `Vizualizer.cpp`
- `test/`
- `CMakeLists.txt`
- `CMakeSettings.json`
- `main.cpp` <- Fri att modifiera
- `README.md`

Alla filer med CMake i namnet är enbart för att alla, oavsett platform, ska kunna kompilera och köra projektet utan att behöva sätta upp nya projekt. För mer information, se sidan Komma igång med CMake i Canvas.

De filer som du ska modifiera är headerfilen `hpp/ConnectN.hpp` och källfilen `src/ConnectN.cpp`. Headerfilen innehåller redan en definition för klassen `ConnectN` som du ska bygga vidare på. Det är viktigt att inte ändra klassnamnet eller ändra funktionsdeklarationerna som redan finns i klassen, men det är helt ok att lägga till extra hjälpfunktioner i klassen om så önskas. Alla funktioner som skapas i klassen `ConnectN` ska *deklareras* i `hpp/ConnectN.hpp`, och ska sedan *definieras* i `srd/ConnectN.cpp`.

Klassen `ConnectN` är ditt *API* för ditt spel. När du granskar koden kommer du se att ett antal funktioner redan finns deklarerade och definierade i `hpp/ConnectN.hpp` respektive `hpp/ConnectN.cpp`, men de behöver definieras klart av dig. Följande funktioner kommer att testas i CodeGrade: 
- `ConnectN::ConnectN`
	- Konstruktor för klassen som kallas när ett objekt av klassens datatyp skapas.
	- Används för att *initiera* klassens medlemsvariabler, exempelvis ange startvärden eller dynamiskt allokera minne.
- `ConnectN::~Connect`
	- Destruktor för klassen som kallas när ett objekt av klassens datatyp förstörs.
	- Används för att *städa upp*, exempelvis frigöra dynamiskt allokerat minne som klassen själv har allokerat.
- `ConnectN::yellowPlays`
	- Funktion för att spela som gul spelare.
	- Tar in vilken kolumn som spelas som argument.
	- Returneras `true` om draget var möjligt, annars `false`
- `ConnectN::redPlays`
	- Funktion för att spela som gul spelare.
	- Tar in vilken kolumn som spelas som argument.
	- Returneras `true` om draget var möjligt, annars `false`
- `ConnectN::getCurrentStatus`
	- Returnerar ett av följande värden:
		- `GamesStatuses::READY` om spelet är redo att starta men inte än har startat.
		- `GamesStatuses::IN_GAME` om spelet har startat och fortfarande spelas.
		- `GamesStatuses::RED_WON` om den röda spelaren har vunnit.
		- `GamesStatuses::YELLOW_WON` om den gula spelaren har vunnit.
		- `GamesStatuses::FULL_BOARD` om spelbrädet är fullt och ingen spelare har vunnit.

Filerna `include/Visualizer.hpp` och `src/Visualizer.cpp` inkluderas för att de automatiska testerna ska kunna visualisera spelbrädet. Detta är inga filer som du behöver använda i ditt program, men det är ok att inkludera `include/Visualizer.hpp` i `main.cpp` om du vill skriva ett eget gränssnitt för spelet. Om du inkluderar denna klass, kom ihåg att lägga till `src/Visualizer.cpp` som källfil till `application` i `CMakeLists.txt`.

## Minnesläckor

I denna uppgift förväntas det att ditt program inte genererar någon minnesläcka, dvs. allt dynamiskt allokerad minne ska deallokeras/frigöras. Vid inlämning kommer en kontroll göras av CodeGrade så att ditt program inte genererar minnesläckor. Memorera följande tumregel:

> Varje allokering med `new` ska senare deallokeras med en korresponderande `delete`. Om `new` används för att allokera en array ska `delete[]` användas istället.

I CodeGrades autotester finns bl.a. **Kompilerar och kör tester med kontroll mot minnesläckor**. Detta test kommer ej att om

1. `auto-tests` ej passerar, eller
2. `auto-tests` genererar minnesläckor från din inlämnade kod.

Om detta test inte passerar i CodeGrade kan du hitta mer information om minnesläckan om du klickar på testets drop-down-meny följt av fliken *Errors*. Följande är ett stycke från ett exempel på en utskrift när en minnesläcka uppstår från minne som har allokerats i klassens konstruktor. Läs detta stycke upp-till-ner, och notera att `ConnectN::ConnectN` (konstruktor) nämns på raden efter `operator new[]`:

```c++
...
==312== 180 bytes in 15 blocks are definitely lost in loss record 1 of 8
==312==    at 0x4C3289F: operator new[](unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==312==    by 0x1EFA92: ConnectN::ConnectN(int, int, int) (in /home/codegrade/student/build/auto-tests)
==312==    by 0x152603: ____C_A_T_C_H____T_E_S_T____101() (in /home/codegrade/student/build/auto-tests)
==312==    by 0x132CB3: Catch::TestInvokerAsFunction::invoke() const (in /home/codegrade/student/build/auto-tests)
==312==    by 0x131F54: Catch::TestCase::invoke() const (in /home/codegrade/student/build/auto-tests)
==312==    by 0x12C5B9: Catch::RunContext::invokeActiveTestCase() (in /home/codegrade/student/build/auto-tests)
==312==    by 0x12C2FE: Catch::RunContext::runCurrentTest(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&) (in /home/codegrade/student/build/auto-tests)
==312==    by 0x12AE09: Catch::RunContext::runTest(Catch::TestCase const&) (in /home/codegrade/student/build/auto-tests)
==312==    by 0x12DE85: Catch::(anonymous namespace)::TestGroup::execute() (in /home/codegrade/student/build/auto-tests)
==312==    by 0x12F1FD: Catch::Session::runInternal() (in /home/codegrade/student/build/auto-tests)
==312==    by 0x12EF06: Catch::Session::run() (in /home/codegrade/student/build/auto-tests)
==312==    by 0x17C932: int Catch::Session::run<char>(int, char const* const*) (in /home/codegrade/student/build/auto-tests)
...
```

En minnesläcka uppstår om ditt program dynamiskt allokerar minne på heapen och inte frigör det när minnet inte längre behövs.

Se följande kodexempel:
```cpp
// Warning: If any of this code feels wierd, please contact your closest teacher assistant immediately.

void IManageMyMemoryCorrectly()
{
	// Dynamically allocating memory on the heap
	int* myArray = new int(42);
	float** myPtrArray = new float*[37];
	
	// ...

	// The dynamically allocated memory are freed
	delete myArray;
	delete[] myPtrArray;
}

void ICreateMemoryLeaks()
{
	// Dynamically allocating memory on the heap
	int* myArray = new int[42];
	float** myPtrArray = new float*[37];

	// ...

	/*
		Leaving the scope will destroy the pointers,
		hince the addresses they store will be lost
		and we can not free the dynamically allocated
		anymore.
	*/
}

void IOnlyAllocate(int*& ptr)
{
	// Dynamically allocating memory on the heap
	ptr = new int(23);
}

IManageMyMemoryCorrectly(); // No memory leaks
ICreateMemoryLeaks(); // Memory leaks

int* myHeapInt;
IOnlyAllocate(myHeapInt); // No memory leak, yet
```