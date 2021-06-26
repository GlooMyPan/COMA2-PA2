#include <iostream>
#include <iomanip>			// f¨¹r setprecision()
#include <cstdlib>			// f¨¹r atoi()
#include <cmath>			// f¨¹r sqrt()
#include "Stoppuhr.h"
#include "PrimTabelle.h"

/***  berechne Primzahlentabelle  ***/

// berechne die Anzahl Teiler von n
// naive Version
size_t anzahlTeilerNaiv ( size_t n )
{
    size_t anzahl = 0;
	for (size_t k = 1; k <= n; ++k)
	    if (n % k == 0)
	        ++anzahl;
    return anzahl;

}

// berechne die Anzahl Teiler von n
// verbesserte Version
size_t anzahlTeilerBesser ( size_t n )
{
	size_t wurzel = size_t(sqrt(n));
	size_t anzahl = 0;
	for (size_t k = 1; k <= wurzel; ++k)
	    if (n % k == 0)
	        anzahl += 2;

    if (wurzel * wurzel == n)
        --anzahl;

    return anzahl;
}


// berechne die Anzahl Teiler von n
// Version mit Division von n
size_t anzahlTeilerDiv ( size_t n )
{
    size_t anzahl = 1;
    size_t p = 2;
    while (n > 1)
    {
        size_t k = 1;
        for (; n % p == 0; n /= p)
            ++k;

        p > 2 ? p += 2 : ++p;
        anzahl *= k;
    }
    return anzahl;
}  // anzahlTeilerDiv()


// berechne die Anzahl Teiler von n
size_t anzahlTeilerPrim(size_t n)
{
    PrimTabelle PrimNumbers;
    size_t index = 0;
    size_t anzahl = 1;
    size_t p = PrimNumbers.primzahl(index);
    size_t wurzel = size_t(sqrt(n));

    while (n > 1)
    {
        size_t k = 1;
        if (p > wurzel) // n ist eine Primzahl
        {
            anzahl *= (k+1); // *= (k_m + 1)
            break;
        }

        for (; n % p == 0; n /= p)
        {
            wurzel = size_t(sqrt(n)); // aktualisierung der wurzel
            ++k;
        }

        anzahl *= k;

        p = PrimNumbers.primzahl(++index);  // suche die n?chste Primzahl

    }
    return anzahl;
}  // anzahlTeilerPrim()

/***
 Bei n_max = 100.000.000 sind die Gewinner 73513440, 82162080, 86486400, 91891800,
                                               98017920, 99459360 mit jeweils 768 Teilern.
 Laufzeiten:
 anzahlTeilerPrim():   267.35s
 anzahlTeilerBesser(): 443.89s
***/

/***
 78472 Primzahlen liegen im Intervall [107,1000007[
 Die mittlere Zahl 500057 ist eine Primzahl.

 807753 Primzahlen liegen im Intervall [12345,12345678[
 Die mittlere Zahl 6179011 ist keine Primzahl.
***/
/***  Hauptprogramm  *************************************************/

int main ( int narg, char* argv[] )
{
	if ( narg < 3 )
	{
		cout << "Usage: " << argv[ 0 ] << "  v  n"		 << endl ;
		cout << "       v: Kennzahl des Verfahrens"		 << endl ;
		cout << "       n: natuerliche Zahl"			 << endl ;
		cout << "Sucht eine nat. Zahl <= n mit den meisten Teilern" << endl ;
		cout << "unter Verwendung des Verfahrens Nr. v." << endl ;
		cout << "v = 1: naive Teilerberechnung"		     << endl ;
		cout << "    2: verbesserte Teilerberechnung"    << endl ;
		cout << "    3: Teilerberechnung mit Division"   << endl ;
		cout << "    4: Teilerberechnung mit Primzahl"   << endl ;
		cout << "  > 4: Anzahl der Primzahlen im Interval [verf, nMax["   << endl ;

		return 0 ;
	}

/***  setze Parameter  ***/

	size_t verf = atoi( argv[ 1 ] ) ;
	size_t nMax = atoi( argv[ 2 ] ) ;

	if ( verf < 1 )
	{
		cout << "Es gibt keine Verfahrensnummer " << verf << endl ;
		return 0 ;
	}

	// init. Zeiger auf die gew¨¹schte Funktion
	auto anzahlTeiler = anzahlTeilerNaiv ;
	if ( verf == 2 )
		anzahlTeiler = anzahlTeilerBesser ;
	if ( verf == 3 )
		anzahlTeiler = anzahlTeilerDiv ;
    if ( verf == 4 )
        anzahlTeiler = anzahlTeilerPrim ;
    if ( verf > 4 )
    {
        PrimTabelle PrimNumbers;

        size_t anzahl = PrimNumbers.index(nMax) - PrimNumbers.index(verf); // mit Indexsubtraktion kriegen wir die Anzahl der Primzahlen im Intervall [verf, nMax[
        size_t middle_number = size_t((nMax + verf)/2); // abruden
        bool istPrim = PrimNumbers.istPrim(middle_number);
        cout << anzahl << " Primzahlen liegen im Intervall [" << verf << "," << nMax << "[" << endl;
        string eine = istPrim ? "eine" : "keine";
        cout << "Die mittlere Zahl " << middle_number << " ist " << eine << " Primzahl.";
        return 0;
    }

/***  bearbeite Aufgabe  ***/

	size_t const NITER = 1 ;
	size_t maxTeiler = 0 ;

    Stoppuhr uhr;
    vector<size_t> maxTeilerNumbers;
    for(size_t i = 0; i < NITER; ++i)
    {
        maxTeilerNumbers.clear();
        for ( size_t n = 1 ;  n <= nMax ;  n == 1 ? ++n : n +=2 ) // grade Zahlen
        {
            size_t teiler = anzahlTeiler( n ) ;

            if (maxTeiler == teiler)
                maxTeilerNumbers.push_back(n);

            if ( maxTeiler < teiler )
            {
                maxTeiler = teiler ;
                maxTeilerNumbers.clear();
                maxTeilerNumbers.push_back(n);
            }
        }
    }
    double laufzeit =  uhr.stopp() / NITER;
    cout << "[ ";
    for (const size_t n : maxTeilerNumbers)
        cout << n << " ";                   // zeigt die Zahlen

    string hat = maxTeilerNumbers.size() > 1 ? " haben " : " hat ";

    cout << "]" << hat << maxTeiler << " Teiler" << endl ;
    cout << "Laufzeit: " << laufzeit << endl;

	return 0 ;

}  // main()

