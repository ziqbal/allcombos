/*
** Find all sets of simple arithmetic mathematical functions that return a whole number 
** Example output in Reverse Polish Notation: 7  3  5  *  8  -  /  2  +  = 3.000000 
** 20141222 , initial release , Zafar Iqbal <ultrasine@gmail.com>
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char alphabet[ 13 ] = {

	'+' , '-' , '*' , '/' ,
	'1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9'  

} ;

int pointers[ 9 ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ;

bool markers[ 13 ] ;

bool done = false ;

int i ;

void resetMarkers( ) {

	markers[ 0 ] = false ;
	markers[ 1 ] = false ;
	markers[ 2 ] = false ;
	markers[ 3 ] = false ;
	markers[ 4 ] = false ;
	markers[ 5 ] = false ;
	markers[ 6 ] = false ;
	markers[ 7 ] = false ;
	markers[ 8 ] = false ;
	markers[ 9 ] = false ;
	markers[ 10 ] = false ;
	markers[ 11 ] = false ;
	markers[ 12 ] = false ;

}

bool isInteger( float val ) {

	return( floorf( val ) == val ) ;

}

void genCombos( ) {

	resetMarkers( ) ;

	for( i = 0 ; i < 9 ; i++ ) {

		if( markers[ pointers[ i ] ] ) return ;

		markers[ pointers[ i ] ] = true ;

	}

	float stack[ 9 ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ;

	int sp = 0 ;

	float val ;

	bool flagOK = true ;

	for( i = 0 ; i < 9 ; i++ ) {

		if( isdigit( alphabet[ pointers[ i ] ] ) ) {

			val = ( float ) alphabet[ pointers[ i ] ] - '0' ;
			stack[ sp++ ] = val ;
			continue ;

		}

		if( sp < 2 ) {

			flagOK = false ;
			break;

		}

		if( alphabet[ pointers[ i ] ] == '+' ) {

			val = stack[ sp - 2 ] + stack[ sp - 1 ] ;
			stack[ sp - 2 ] = val ;
			sp-- ;

			continue ;

		}

		if( alphabet[ pointers[ i ] ] == '-' ) {

			val = stack[ sp - 2 ] - stack[ sp - 1 ] ;
			stack[ sp - 2 ] = val ;
			sp-- ;
			continue ;

		}

		if( alphabet[ pointers[ i ] ] == '*' ) {

			val = stack[ sp - 2 ] * stack[ sp - 1 ] ;
			stack[ sp - 2 ] = val ;
			sp-- ;
			continue;

		}

		if( alphabet[ pointers[ i ] ] == '/' ) {

			if( stack[ sp - 1 ] == 0.0 ) {

				flagOK = false ;
				break ;

			}

			val = stack[ sp - 2 ] / stack[ sp - 1 ] ;
			stack[ sp - 2 ] = val ;
			sp-- ;
			continue ;

		}

		flagOK = false ;
		break;

	}

	if( !flagOK ) return ;
	if( sp != 1 ) return ;

	if( !isInteger( stack[ 0 ] ) ) return ;

	for( i = 0 ; i < 9 ; i++ ) {

		printf( " %c " , alphabet[ pointers[ i ] ] ) ;

	}

	printf( " = %f \n" , stack[ 0 ] ) ;

}

void nextWord( ) {

	for( int i = 0 ; i < 9 ; i++ ) {

		pointers[ i ] ++ ;

		if( pointers[ i ] < 13 ) return ;

		pointers[ i ] = 0 ;

	}


	done = true ;

}

int main( ) {

	while( ! done ) {

		genCombos( ) ;

		nextWord( ) ;

	}

	return( 0 ) ;

}

