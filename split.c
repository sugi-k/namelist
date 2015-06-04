#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void split( char *s, char *substr[], char sep, int n ) {
  char *s2;
  int i;
  for ( i = 0; i < n; i++ ) {
    substr[ i ] = ( char* )malloc( sizeof( char ) * strlen( s ) );
    s2 = substr[ i ];
    while ( ( *s != sep )&&( *s != '\0' ) ){
      *s2++ = *s++;
    }
    *s2 = '\0';
    s++;
  }
}

int main(){
  char line[ 1024 ];
  char *data[ 5 ];
  char *data2[ 3 ];
  int i, j;
  fgets( line, 1024, stdin );
  split( line, data, ',', 5 );
  split( data[2], data2, '-', 3 );
  for ( i = 0; i < 5; i++ ){
    if ( i != 2 ){
      printf( "%s/", data[ i ] );
    }else{
      for( j = 0; j < 3; j++ ){
	printf( "%s/", data2[ j ]);
      }
    }
  }
  return 0;
}
