# Inlämningsuppgift 3, 'Custom vector'

## Snabblänkar till mallar och inlämningssidor

- **Kodmall:**
- **Tillfälle 1:**
- **Tillfälle 2:**
- **Tillfälle 3:**

# Innehåll

- Syfte
- Uppgift
	- Vad är en generisk behållare?
- Kriterier
- Komma igång
	- Att tänka på
	- Tips under implementation
- Minnesläckor

# Syfte

Denna uppgift ska examinera dig på:

- Hantering av dynamiskt allokerat minne
- Generisk programmering

> Detta är en individuell examination. All kod du lämnar in ska vara skriven av dig och enbart dig, med undantag för den kod som följer med i uppgiftsmallen. Det kommer att utföras en plagieringskontroll på inlämnad kod. Var noga att inte dela din egen kod med andra personer då båda era inlämningar kommer flaggas som plagiat.

# Uppgift

Du ska skapa en egen verison av klassen `std::vector` från standardbiblioteket. Din egen behållare med namnet `Vector` ska vara en behållare som hanterar ett godtyckligt antal objekt av godtycklig datatyp, och med funktionalitet att öka sin kapacitet om nödvändigt. För att `Vector` ska kunna hantera godtycklig datatyp behöver klassen vara en *klassmall* (`template`).

## Vad är en generisk behållare?

I C++ kan ett antal objekt hanteras i en array, däremot kan inte arrayer öka sin storlek. Vad du som programmerare behöver göra är att allokera en ny array, flytta alla objekt från den gamla arrayen till den nya och frigöra den gamla arrayen.

En array är enbart *ett antal objekt som ligger sekventiellt (direkt efter varandra) i minnet. Tack vare detta kan vi komma åt alla element i arrayen genom att veta var det första elementet börjar i minnet, sen hoppa till önskat antal bytes från denna adress. Detta är varför en array sparas med en pekare; pekaren innehåller bara adressen till det första elementet. För att läsa exempelvis element på index `4` hoppar vi dit och derefererar pekaren:

```cpp
// 'startOfArray' is an array of random ints
std::cout << *(startOfArray + 4) << std::endl;

// The following is the same as above, and is 
// more convenient
std::cout << startOfArray[4] << std::endl;
```
En *behållare* är ett objekt som hanterar denna array åt programmeraren. Om dess kapacitet inte räcker till så kommer behållaren att hantera detta automatiskt. En *generisk* behållare kan hantera godtycklig datatyp, se detta exempel med `std::vector`:

```cpp
std::vector<int> intVector;
intVector.push_back(51);

std::vector<float> floatVector;
floatVector.push_back(42.12f);

std::vector<std::string> stringVector;
stringVector.push_back("This is a string");
```


# Kriterier

**För betyget G ska följande kriterier vara uppfyllda:**

1. Element ska sparas internt i en **dynamisk array** av en generisk datatyp (`template`).
    - Arrayen ska allokeras på heapen och initieras med en rimlig kapacitet (ca. `10-50`).
    - Om fler objekt läggs till i `Vector`-objektet än vad kapaciteten tillåter ska en ny array allokeras med ökad kapacitet och alla existerande element ska kopieras/flyttas till den nya arrayen.
    - Denna array måste sparas med en **rå pekare** (dvs. inte en *smart pointer*).
    - Alla element ska vara tätt packade, det får alltså inte lämnas *tomma positioner* mellan första och sista elementet.
2. Alla funktionskallelser och argument som *kan* vara felaktiga *ska* kontrolleras och **hanteras på ett rimligt sätt**.
3. Det får **inte** uppstå minnesläckor.

**För inlämnad kod ska följande uppfyllas:**

- Allt som bör vara `const`, ska vara `const`.
- Allt som bör vara `public`, ska vara `public`.
- Allt som bör vara `private`, ska vara `private`.
- Variabler och parametrar ska ha självbeskrivande namn.

# Komma igång

1. Skapa en klassmall (`template`) med namnet `Vector` i headerfilen `Vector.hpp`.
2. Deklarera privata medlemsvariabler och publika medlemsfunktioner enligt tabellen nedan.**
    - Det är tillåtet och rekommenderat att lägga till egna medlemsvariabler och medlemsfuntioner så länge de är *privata*.
3. Gör egna tester och verifiera att din vektor fungerar korrekt `main.cpp`.
4. Verifiera att din klass passerar alla automatiska enhetstester

| Namn                                          | Kommentar     |
|-----------------------------------------------|---------------|
| `- m_elements : T*`                           | Den underliggande arrayen som innehåller alla objekt. |
| `- m_nrOfElements : int`                      | Antalet element i arrayen som för tillfället används. |
| `- m_capacity : int`                          | Antalet platser som för tillfället är allokerat för den underliggande arrayen. |
||
| `+ Vector()`                                  | Initerar vektorn med en standardstorlek.                    |
| `+ ~Vector()`                                 | Sätter vektorn i ett förstörbart skick.                     |
||
| `+ Vector(const Vector& other)`               | Initierar vektorn som en kopia av en annam vektor.          |
| `+ Vector& operator=(const Vector& other)`    | Gör den tilldelade vektorn till en kopia av en annan vektor.|
||
| `+ Vector(Vector&& other)`                    | Vektorn initieras och tar över ansvaret av allt innehåll från en annan vektor. Den andra vektorn ska lämnas i ett förstörbart skick. |
| `+ Vector& operator=(Vector&& other)`         | Vektorn tar över ansvaret av allt innehåll från en annan vektor. Den andra vektorn ska lämnas i ett förstörbart skick. |
||
| `+ at(const int index) const : T&`            | Returnerar ett specifikt element på *giltigt* index. |
| `+ operator[](const int index) const : T&`    | Returnerar ett specifikt element på *giltigt* index. |
| `+ front() const : T&`                        | Returnerar det första elementet i vektorn. |
| `+ back() const : T&`                         | Returnerar det sista elementet i vektorn. |
| `+ data() const : const T*`                   | Returnerar en konstantpekare till den underliggande arrayen. |
||
| `+ size() const : int`                        | Returnerar antalet objekt som för tillfället finns sparade som element i vektorn. |
| `+ capacity() const : int`                    | Returnerar kapaciteten på den underliggande arrayen. Notera att arrayen kan innehålla platser som inte *används*. |
| `+ empty() const : bool`                      | Returnerar `true` om vektorn inte innehåller några objekt, annars `false`. |
||
| `+ clear() : void`                            | Tömmer vektorn på alla objekt. |
| `+ insert(const int index, const T& element) : void`  | Placerar ett nytt objekt på ett *giltigt* index. Det ska vara möjligt lägga till ett objekt först, sist, eller någonstans i mitten av vektorn. |
| `+ erase(const int index) : void`             | Tar bort ett objekt från ett *giltigt* index. |
| `+ push_back(const T& element) : void`        | Placerar ett nytt objekt längst bak i vektorn. |
| `+ pop_back() : void`                         | Tar bort det sista objekt i vektorn. |

Vektorn förväntas att hantera sin storlek automatiskt. En array ska initeras med en viss storlek, och detta betyder inte att alla element *används*. När ett nytt objekt läggs till i vektorn ska *nästa ej använda element* skrivas över med det nya objektet. Om den underliggande arrayen blir full, och ett nytt objekt läggs till, så ska vektorn:

1. Allokera en ny dynamisk array. Denna ska vara större än den nuvarande för att hantera fler element.
2. Kopiera över alla nuvarande element till den nya arrayen.
3. Deallokera den tidigare arrayen.
4. Spara den nya arrayen som underliggande array.

## Att tänka på

- Det är **inte** tillåtet att använda en färdig behållare internt för att spara element.
- Skapas en större array måste även kapacitetsvariablen uppdateras med den nya storleken.
- Den interna arrayen får inte innehålla hål. Alla element ska vara placeras direkt efter varandra. Om ett element tas bort i mitten av arrayen ska resterande element justeras **utan att ändra ordningen på dem**.

## Tips under implementation

- Kompilera ofta! Detta gör att du lättare vet var fel uppstår.
- Tänk noga igenom alla möjliga värden ett argument kan ha. Finns det något utfall som kan ställa till med problem? Hur ska det hanteras?
- Ta en bensträckare med jämna mellanrum! Oftast är det vid pauser man inser vad en bugg beror på.
- Kommer funktionen modifiera medlemsvariabler? Om inte, ange den som `const`!
- Får du felmeddelanden? Testa googla dem! Brukar alltid vara någon som fått samma problem på något forum. :)

# Minnesläckor

I denna uppgift förväntas det att ditt program inte genererar någon minnesläcka, dvs. allt dynamiskt allokerad minne ska deallokeras/frigöras. Vid inlämning kommer en kontroll göras av CodeGrade så att ditt program inte genererar minnesläckor. Memorera följande tumregel:

> Varje allokering med `new` ska senare deallokeras med en korresponderande `delete`. Om `new` används för att allokera en array ska `delete[]` användas istället.

I CodeGrades autotester finns bl.a. **Kompilerar och kör tester med kontroll mot minnesläckor**. Detta test kommer ej att om

1. `auto-tests` ej passerar, eller
2. `auto-tests` genererar minnesläckor från din inlämnade kod.

Om detta test inte passerar i CodeGrade kan du hitta mer information om minnesläckan om du klickar på testets drop-down-meny följt av fliken *Errors*. Följande är ett stycke från ett exempel på en utskrift när en minnesläcka uppstår från minne som har allokerats i klassens konstruktor. Läs detta stycke upp-till-ner, och notera att `Vector<DynamicType>::Vector(Vector<DynamicType> const&)` är funktionen som nämns på raden efter `operator new[]`. Detta betyder att denna funktion *allokerar minne som inte blir deallokerat korrekt* innan programmet avslutas.

```c++
...
==313== 128 (88 direct, 40 indirect) bytes in 1 blocks are definitely lost in loss record 21 of 220
==313==    at 0x4C3289F: operator new[](unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==313==    by 0x208C1B: Vector<DynamicType>::Vector(Vector<DynamicType> const&) (in /home/codegrade/student/build/auto-tests)
==313==    by 0x18D994: void ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____455<42, Vector<DynamicType> >() (in /home/codegrade/student/build/auto-tests)
==313==    by 0x133013: Catch::TestInvokerAsFunction::invoke() const (in /home/codegrade/student/build/auto-tests)
==313==    by 0x1322B4: Catch::TestCase::invoke() const (in /home/codegrade/student/build/auto-tests)
==313==    by 0x12C919: Catch::RunContext::invokeActiveTestCase() (in /home/codegrade/student/build/auto-tests)
==313==    by 0x12C65E: Catch::RunContext::runCurrentTest(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&) (in /home/codegrade/student/build/auto-tests)
==313==    by 0x12B169: Catch::RunContext::runTest(Catch::TestCase const&) (in /home/codegrade/student/build/auto-tests)
==313==    by 0x12E1E5: Catch::(anonymous namespace)::TestGroup::execute() (in /home/codegrade/student/build/auto-tests)
==313==    by 0x12F55D: Catch::Session::runInternal() (in /home/codegrade/student/build/auto-tests)
==313==    by 0x12F266: Catch::Session::run() (in /home/codegrade/student/build/auto-tests)
==313==    by 0x1D8A94: int Catch::Session::run<char>(int, char const* const*) (in /home/codegrade/student/build/auto-tests)
...
```

En minnesläcka uppstår om ditt program dynamiskt allokerar minne på heapen och inte frigör det när minnet inte längre behövs.

Se följande kodexempel:
```cpp
// Warning: If any of this code feels wierd, please contact your closest teacher assistant immediately.

void IManageMyMemoryCorrectly()
{
	// Dynamically allocating memory on the heap
	int* myInt = new int(42);
	int* myArray = new int[85];
	float** myPtrArray = new float*[37];
	
	// ...

	// The dynamically allocated memory are freed
	delete myInt;
	delete[] myArray;
	delete[] myPtrArray;
}

void ICreateMemoryLeaks()
{
	// Dynamically allocating memory on the heap
	int* myInt = new int(42);
	int* myArray = new int[85];
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
IOnlyAllocate(myHeapInt); // No memory leak, yet, but needs to be deallocated
```
