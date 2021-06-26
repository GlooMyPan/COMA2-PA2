#ifndef STOPPUHR_H
#define STOPPUHR_H

#include <iostream>
#include <ctime>			// für clock()

using namespace std ;


/**
 * einfache Klasse zur Zeitmessung
 * Autor: Martin Oellrich
 */

class Stoppuhr
{
/***  private Attribute  ***/

	// letzte Startzeit
	double _startZeit ;

public:
/***  Konstruktoren  ***/

	// Standardkonstruktor, startet Zeitmessung
	Stoppuhr ()
	{
		start() ;
	}

/***  get-Methoden  ***/

	// gib laufende Zeit aus, halte Zeitmessung nicht an
	double stopp () const
	{
		return ( clock() - _startZeit ) / CLOCKS_PER_SEC ;
	}

/***  set-Methoden  ***/

	// starte Messung neu
	void start ()
	{
		_startZeit = clock() ;
	}

} ;  // class Stoppuhr


/***  Ausgabe auf ostream  ***/

inline
ostream& operator << ( ostream& ostr, Stoppuhr const& uhr )
{
	return ostr << uhr.stopp() << " s" ;
}


#endif  // STOPPUHR_H