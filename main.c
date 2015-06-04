#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct Date{ 
  /*設立年月日の構造体*/
  int year;
  int month;
  int day;
}Date;

typedef struct Profile{
  /*データの格納場所の構造体*/
  int id;
  char name[70];
  Date est_date;
  char address[70];
  char other[256];
}Profile;

void initialization( Profile *array, int n )
{/*n番目の配列の初期化*/
  int i;
  array[n].id = 0;
  for ( i = 0; i < 70; i++ ){
    array[n].name[i] = '\0';
    array[n].address[i] = '\0';
  }
  (array[n].est_date).year = 0;
  (array[n].est_date).month = 0;
  (array[n].est_date).day = 0;
  for ( i = 0; i < 256; i++ ) {
    array[n].other[i] = '\0';
  }
}

int split( char *s, char *substr[], char sep, int n ) 
{/*データを分割する関数*/
  char *s2;
  int i, j = 1;
  for ( i = 0; i < n; i++ ) {
    /*ポインタの配列の指す先を確保する*/
    substr[ i ] = ( char* )malloc( sizeof( char ) * strlen( s ) );
    s2 = substr[ i ];
    while ( ( *s != sep )&&( *s != '\0' ) ){
      if ( *s != '\n' ) {
	*s2 = *s;
      }
      *s2++;
      *s++;
    }
    if ( *s == sep ) {
      j++;
    }
    *s2 = '\0';
    s++;
  }
  return j;
}

int ad_split( char line[], Profile data[] , int input_n ) 
{/*splitを呼ぶための前準備とデータのProfile型化*/
  char *ad_data[5];
  char *ad_data2[3];
  int i;
  if ( split( line, ad_data, ',', 5 ) != 5 ) {/*不正な入力の検出*/
    return 2;/*input関数用*/
  }
  if ( split( ad_data[2], ad_data2, '-', 3 ) != 3 ) {/*不正な入力の検出*/
    return 2;
  }
  /*分けた値を構造体に代入*/
  data[input_n].id = atoi( ad_data[0] );
  strcpy( data[input_n].name, ad_data[1] );
  (data[input_n].est_date).year = atoi( ad_data2[0] );
  (data[input_n].est_date).month = atoi( ad_data2[1] );
  (data[input_n].est_date).day = atoi( ad_data2[2] );
  strcpy( data[input_n].address, ad_data[3] );
  strcpy( data[input_n].other, ad_data[4] );

  return 0;
}

void input( int *i ) 
{/*コマンドを入力するときに表示される言葉*/
  if ( *i == 0 ) {
    printf( "データもしくはコマンドを" );
  } else if ( *i == 1 ){
    printf( "そのようなコマンドは存在しませんもう一度" );
  } else {
    printf( "不正な入力です，もう一度" );
  }
  printf( "入力してください．\n" );
  *i = 0;
  return;
}

void myprint( Profile data[], int i )
{/*データの表示*/
    printf( "ID\t:%d\n", data[i].id );
    printf( "NAME\t:%s\n", data[i]. name );
    printf( "DATE\t:%d/%d/%d\n", (data[i].est_date).year, 
	    (data[i].est_date).month, (data[i].est_date).day );
    printf( "Addr\t:%s\n", data[i].address );
    printf( "Misc\t:%s\n", data[i].other );
    printf( "\n" );
}

void ASwap( Profile *array, int x, int y )
{/*配列の要素入れ替え*/
  Profile tmpSw;
  tmpSw = array[x];
  array[x] = array[y];
  array[y] = tmpSw;
}

int partition_id( Profile *array, int left, int right )
{/*IDの分割関数*/
  int i = left - 1;
  int j = right;
  int v = array[right].id;
  while (1) {
    while ( array[++i].id < v );
    while ( v < array[--j].id ) {
      if( j == left ) {
	break;
      }
    }
    if ( i >= j ) {
      break;
    }
    ASwap( array, i, j );
  }
  ASwap( array, i, right );
  return i;
}

void Qsort_id( Profile *array, int left, int right )
{/*IDのクイックソート*/
  int i;
  if ( right <= left ) {
    return;
  }
  i = partition_id( array, left, right );
  Qsort_id( array, left, i - 1 );
  /*基準値より小さい部分のクイックソート*/
  Qsort_id( array, i + 1, right );
  /*基準値より大きい部分のクイックソート*/
  return;
}

int Protoi( Profile *array, int x )
{/*設立年月日のProfile型をint型に変換*/
  int i;
  i = ( ( array[x].est_date ).year * 10000 );
  i += ( ( array[x].est_date ).month * 100 );
  i += ( ( array[x].est_date ).day );
  return i;
}

int partition_date( Profile *array, int left, int right )
{/*設立年月日の分割関数*/
  int i = left - 1;
  int j = right;
  int v = Protoi( array, right );
  while (1) {
    ++i;
    while ( Protoi( array, i ) < v ) {
      i++;
    }
    --j;
    while ( v < Protoi( array, j ) ) {
      --j;
      if( j == left ) {
	break;
      }
    }
    if ( i >= j ) {
      break;
    }
    ASwap( array, i, j );
  }
  ASwap( array, i, right );
  return i;
}

void Qsort_date( Profile *array, int left, int right )
{/*設立年月日のクイックソート*/
  int i;
  if ( right <= left ) {
    return;
  }
  i = partition_date( array, left, right );
  Qsort_date( array, left, i - 1 );
  /*基準値より小さい部分のクイックソート*/
  Qsort_date( array, i + 1, right );
  /*基準値より大きい部分のクイックソート*/
  return;
}

int partition_name( Profile *array, int left, int right )
{/*学校名の分割関数*/
  int i = left - 1;
  int j = right;
  char v[70] = {0};
  int n;
  for ( n = 0; array[right].name[n] != '\0'; n++ ) {
    v[n] = array[right].name[n];
  }
  while (1) {
    ++i;
    while ( strcmp( array[i].name, v ) < 0 ) {
      ++i;
    }
    --j;
    while ( strcmp( v, array[j].name ) < 0 ){
      --j;
      if( j == left ) {
	break;
      }
    }
    if ( i >= j ) {
      break;
    }
    ASwap( array, i, j );
  }
  ASwap( array, i, right );
  return i;
}

void Qsort_name( Profile *array, int left, int right )
{/*学校名のクイックソート*/
  int i;
  int j;
  if ( right <= left ) {
    return;
  }
  i = partition_name( array, left, right );
  Qsort_name( array, left, i - 1 );
  /*基準値より小さい部分のクイックソート*/
  Qsort_name( array, i + 1, right );
  /*基準値より大きい部分のクイックソート*/
  return;
}

int partition_address( Profile *array, int left, int right )
{/*所在地の分割関数*/
  int i = left - 1;
  int j = right;
  char v[70] = {0};
  int n;
  for ( n = 0; array[right].address[n] != '\0'; n++ ) {
    v[n] = array[right].address[n];
  }
  while (1) {
    ++i;
    while ( strcmp( array[i].address, v ) < 0 ) {
      ++i;
    }
    --j;
    while ( strcmp( v, array[j].address ) < 0 ){
      --j;
      if( j == left ) {
	break;
      }
    }
    if ( i >= j ) {
      break;
    }
    ASwap( array, i, j );
  }
  ASwap( array, i, right );
  return i;
}

void Qsort_address( Profile *array, int left, int right )
{/*所在地のクイックソート*/
  int i;
  int j;
  if ( right <= left ) {
    return;
  }
  i = partition_address( array, left, right );
  Qsort_address( array, left, i - 1 );
  /*基準値より小さい部分のクイックソート*/
  Qsort_address( array, i + 1, right );
  /*基準値より大きい部分のクイックソート*/
  return;
}

int partition_other( Profile *array, int left, int right )
{/*備考データの分割関数*/
  int i = left - 1;
  int j = right;
  char v[256] = {0};
  int n;
  for ( n = 0; array[right].other[n] != '\0'; n++ ) {
    v[n] = array[right].other[n];
  }
  while (1) {
    ++i;
    while ( strcmp( array[i].other, v ) < 0 ) {
      ++i;
    }
    --j;
    while ( strcmp( v, array[j].other ) < 0 ){
      --j;
      if( j == left ) {
	break;
      }
    }
    if ( i >= j ) {
      break;
    }
    ASwap( array, i, j );
  }
  ASwap( array, i, right );
  return i;
}

void Qsort_other( Profile *array, int left, int right )
{/*備考データのクイックソート*/
  int i;
  int j;
  if ( right <= left ) {
    return;
  }
  i = partition_other( array, left, right );
  Qsort_other( array, left, i - 1 );
  /*基準値より小さい部分のクイックソート*/
  Qsort_other( array, i + 1, right );
  /*基準値より大きい部分のクイックソート*/
  return;
}

void exec_command_Q()
{
  /*コマンドQ,終了のコマンドの関数*/
  printf("終了します．\n");
  exit(0);
}

void exec_command_C( int n )
{/*コマンドC,登録内容の確認のコマンドの関数*/
  printf( "登録件数は%d件です．\n", n );
}

void exec_command_P( int n, Profile data[], int reg_n )
{/*コマンドP,表示のコマンドの関数*/
  int i = 0;/*出力の開始位置*/
  
  if ( n > reg_n ) {/*データ数より多い数が入力されたとき*/
    printf( "登録数より多い値が入力されています．\n" );
    return;
  }
  if( n == 0 ) {/*全表示のときの場合*/
    n = reg_n;
  } 
  if ( n < 0) {/*後ろからn件表示*/
    i = reg_n + n;
    n = reg_n;
  }
  while( i < n ){/*データをiからnまで表示*/
    myprint( data, i );
    i++;
  }
}


int exec_command_R( char command[], FILE *fp, Profile data[], int input_n )
{/*コマンドR,ファイルの読み込み*/
  char input_array[1024];/*の配列*/
  char file_name[32] = {0};/*ファイルの名前*/
  int input_n_R = 0;/*入力が成功すれば0,失敗すれば2になる*/
  int i = 3, j;
  while ( command[i] != '.' ) {
    file_name[i - 3] = command[i];
    i++;
  }
  for ( j = 0; j < 4; j++ ){
    file_name[i - 3] = command[i];
    i++;
  }
  fp = fopen( file_name, "r" );
  if ( fp == NULL ) {
    printf( "ファイルの読み込みに失敗しました．" );
    return 0;
  }
  i = 0;
  while ( fgets( input_array, sizeof( input_array ), fp ) != NULL ) {
    input_n_R = ad_split( input_array, data, input_n );
    input_n++;
    if ( input_n_R == 0 ) {
      i++;
    } else {
      printf( "ファイルの%d行目の記述が正確ではありません．", i );
    }
  }
  fclose( fp );
  printf( "ファイルの読み込みが終了しました．\n" );
  return i;
}

void exec_command_W( char command[], FILE *fp, Profile data[], int reg_n )
{/*コマンドW,ファイルへの書き込み*/
  int i = 3, j;
  char file_name[32];/*ファイル名*/
  while ( command[i] != '.' ) {
    file_name[i - 3] = command[i];
    i++;
  }
  for ( j = 0; j < 4; j++ ){
    file_name[i - 3] = command[i];
    i++;
  }
  file_name[i - 3] = '\0';
  fp = fopen( file_name, "w" );
  if ( fp == NULL ) {
    printf( "ファイルの読み込みに失敗しました．" );
    return;
  }
  for ( i = 0; i < reg_n; i++ ) {
    fprintf( fp, "%d,%s,%d-%d-%d,%s,%s\n", 
	     data[i].id,
	     data[i].name,
	     ( data[i].est_date ).year,
	     ( data[i].est_date ).month,
	     ( data[i].est_date ).day,
	     data[i].address,
	     data[i].other );
  }
  fclose( fp );
}

void exec_command_F( char command[], Profile data[], int reg_n )
{/*コマンドF,文字列の探索*/

  char word[1024];/*探索する文字列*/
  int i, tmpFi;

  for( i = 0; command[i + 3] != '\n'; i++ ) {
    word[i] = command[i + 3];
  }
  tmpFi = atoi( word );
  for ( i = 0; i < reg_n; i++ ) {
    if ( ( tmpFi == data[i].id ) || 
	 ( tmpFi == ( ( data[i].est_date ).year ) ) || 
	 ( tmpFi == ( ( data[i].est_date ).month ) ) || 
	 ( tmpFi == ( ( data[i].est_date ).day ) ) ||
	 ( strstr( data[i].name, word ) ) ||
	 ( strstr( data[i].address, word ) )  ||
	 ( strstr( data[i].other, word ) ) ) {
      myprint( data, i );
    }
  }
}
void exec_command_S( char command[], Profile data[], int reg_n )
{/*コマンドS,ソート*/
  int mode;
  mode = atoi( command+3 );
  while ( mode ) {/*modeの値が0(終了)になるまで繰り返し*/
    switch( mode ){
    case 1:
      Qsort_id( data, 0, reg_n - 1 );
      printf( "IDでソートしました．\n" );
      mode = 0;
      break;
    case 2:
      Qsort_name( data, 0, reg_n - 1 );
      printf( "学校名でソートしました．\n" );
      mode = 0;
      break;
    case 3:
      Qsort_date( data, 0, reg_n - 1 );
      printf( "設立年月日でソートしました．\n" );
      mode = 0;
      break;
    case 4:
      Qsort_address( data, 0, reg_n - 1 );
      printf( "所在地でソートしました．\n" );
      mode = 0;
      break;
    case 5:
      Qsort_other( data, 0, reg_n - 1 );
      printf( "備考データでソートしました．\n" );
      mode = 0;
      break;
    default:
      printf( "ソートは以下の数字から選んでください.\n" );
      printf( "1:ID 2:学校名 3:設立年月日 4:所在地 5:備考データ 0:終了" );
      scanf( "%d", &mode );
      break;
    }
  }
}

void exec_command_D( char command[], Profile data[], int *reg_n )
{/*コマンドD,登録内容の削除*/
  int i, j;
  for ( i = 0; i < *reg_n; i++) {
    if ( atoi( command+3 ) == data[i].id ) {
      for ( j = i; j < *reg_n - 1; j++ ) {
	data[j] = data[j + 1];
      }
      initialization( data, *reg_n - 1 );
      (*reg_n)--;
    }
  }
  printf( "削除が終了しました．" );
}


int main()
{
  char command[1024];/*コマンドまたはデータ入力用*/
  Profile data[10000];/*入力データの配列*/
  FILE *fp;/*ファイルポインタ*/
  int input_v = 0;/*入力用の制御変数*/
  int reg_n = 0;/*登録件数*/
  int i;
  for ( i = 0; i < 10000; i++ ) {
    initialization( data, i );
  }
  printf( "名簿管理システム\n" );
  while ( 1 ) {
    input ( &input_v );
    fgets( command, sizeof( command ), stdin );
    if( command[0] == '%' ){/*コマンドの条件分岐*/
      switch( toupper( command[1] ) ){
      case 'Q':/*終了*/
	exec_command_Q();
	break;
      case 'C':/*登録内容の確認*/
	exec_command_C( reg_n );
	break;
      case 'P':/*n件表示*/
	exec_command_P( atoi( command+3 ), data, reg_n );
	break;
      case 'R':/*ファイルの読み込み*/
	reg_n += exec_command_R( command, fp, data, reg_n );
	break;
      case 'W':/*ファイルへの書き込み*/
	exec_command_W( command, fp, data, reg_n );
	break;
      case 'F':/*ワードの探索*/
	exec_command_F( command, data, reg_n );
	break;
      case 'S':/*ソート*/
	exec_command_S( command, data, reg_n );
	break;
      case 'D':/*削除*/
	exec_command_D( command, data, &reg_n );
	break;
      default:/*定義されている以外のコマンド*/
	input_v = 1;
	break;
      }
    } else {
      /*データ入力と入力エラーチェック*/
      input_v = ad_split( command, data, reg_n );
      /*正しい入力ならデータ数+1間違えならエラー*/
      if ( input_v == 0 ) {
        reg_n++;
      } else {
        input_v = 2;
      }
    }
  }
  return 0;
}

