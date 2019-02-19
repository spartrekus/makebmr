

#include <stdio.h>
#if defined(__linux__)
#define MYOS 1
#elif defined(_WIN32)
#define MYOS 2
#elif defined(_WIN64)
#define MYOS 3
#elif defined(__unix__)
#define MYOS 4
#define PATH_MAX 2500
#else
#define MYOS 0
#endif
#include <string.h>
#include <stdlib.h>

#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h> 
#include <time.h>

#include <dirent.h>
#include <errno.h>


char pathbefore[PATH_MAX];




void ncp( char *targetfile, char *sourcefile )
{

   FILE *source, *target; 
   int ch ; 
   source = fopen( sourcefile , "r");
   if( source == NULL )
   {
      printf("Press any key to exit...\n");
      exit(EXIT_FAILURE);
   }
 
   target = fopen( targetfile , "w");
   if( target == NULL )
   {
      fclose(source);
      printf("Press any key to exit...\n");
      exit(EXIT_FAILURE);
   }
 
   printf("  >Source: %s\n",  sourcefile );
   printf("  >Target: %s\n",  targetfile );
   printf("  >Copying...\n");

   while( ( ch = fgetc(source) ) != EOF )
      fputc(ch, target);
 
   printf("File copied successfully.\n");
   fclose(source);
   fclose(target);
}






/////////////////////////////////
int filecheck( char *myfoofile )
{
   printf( " FILECHECK \n" );
   int valret = 0;
   FILE *foosource;
   foosource = fopen( myfoofile , "r");
   if ( foosource == NULL ) 
   {  
     printf( " File %s not found.\n",    myfoofile ); 
     printf( " filecheck: %s failed.\n", myfoofile );
     valret = 0;
   } else {
     printf( " filecheck: %s OK \n", myfoofile );
     valret = 1;
   }
   fclose( foosource );
   return valret;
}










int dircheck( char *mydir )
{
   int valret = 0;
   DIR* dir = opendir( mydir );
   if (dir)
   {
     /* Directory exists. */
     closedir(dir);
     printf( "dircheck: %s does exists \n", mydir );
     valret = 2;
   }
   else if (ENOENT == errno)
   {
    /* Directory does not exist. */
     printf( "dircheck: %s does not exists \n", mydir );
     valret = 0;
   }
   else
   {
    /* opendir() failed for some other reason. */
     printf( " dircheck: %s failed \n", mydir );
     valret = -1;
   }
   return valret;
}





/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
int fexist(char *a_option)
{
  char dir1[PATH_MAX]; 
  char *dir2;
  DIR *dip;
  strncpy( dir1 , "",  PATH_MAX  );
  strncpy( dir1 , a_option,  PATH_MAX  );

  struct stat st_buf; 
  int status; 
  int fileordir = 0 ; 

  status = stat ( dir1 , &st_buf);
  if (status != 0) {
    fileordir = 0;
  }

  // this is compatible to check if a file exists
  FILE *fp2check = fopen( dir1  ,"r");
  if( fp2check ) {
  // exists
  fileordir = 1; 
  fclose(fp2check);
  } 

  if (S_ISDIR (st_buf.st_mode)) {
    fileordir = 2; 
  }
return fileordir;
/////////////////////////////
}





void nls()
{ 
   DIR *dirp;
   struct dirent *dp;
   dirp = opendir( "." );
   while  ((dp = readdir( dirp )) != NULL ) 
   {
         if (  strcmp( dp->d_name, "." ) != 0 )
         if (  strcmp( dp->d_name, ".." ) != 0 )
             printf( "%s\n", dp->d_name );
   }
   closedir( dirp );
}





void printdir()
{
   DIR *dirp; int chr ;  
   struct dirent *dp;
   dirp = opendir( "." );
   while  ((dp = readdir( dirp )) != NULL ) 
   {
        if (  strcmp( dp->d_name, "." ) != 0 )
        if (  strcmp( dp->d_name, ".." ) != 0 )
        {
            for ( chr = 0 ;  chr <= strlen(dp->d_name) ; chr++) 
               printf( "%c" , dp->d_name[chr] );
            printf( "\n" );
        }
   }
   closedir( dirp );
}






void ncpbmr( char *mytrgdir , char *mysrcdir )
{ 
   printf( " NCP: %s %s\n" , mytrgdir ,  mysrcdir );
   DIR *dirp;
   char foostr[PATH_MAX];
   char ncpfsrc[PATH_MAX];
   char ncpftrg[PATH_MAX];
   struct dirent *dp;
   dirp = opendir( "." );
   while  ((dp = readdir( dirp )) != NULL ) 
   {
         if (  strcmp( dp->d_name, "." ) != 0 )
         if (  strcmp( dp->d_name, ".." ) != 0 )
         {
            printf( "TRG:%s  SRC:%s\n", mytrgdir ,  mysrcdir );
            printf( "%s\n", dp->d_name );
            printf( " F:%d\n", fexist( dp->d_name ) );
            printf( " D:%d\n", dircheck(  dp->d_name ) );

               strncpy( foostr , mysrcdir , PATH_MAX );
               strncat( foostr , "/" , PATH_MAX - strlen( foostr ) -1 );
               strncat( foostr , dp->d_name  , PATH_MAX - strlen( foostr ) -1 );
               strncpy( ncpfsrc, foostr , PATH_MAX );

               strncpy( foostr , mytrgdir , PATH_MAX );
               strncat( foostr , "/" , PATH_MAX - strlen( foostr ) -1 );
               strncat( foostr , dp->d_name  , PATH_MAX - strlen( foostr ) -1 );
               strncpy( ncpftrg, foostr , PATH_MAX );

               printf( " I:FILE SRC %s\n", ncpfsrc );
               printf( " I:FILE TRG %s\n", ncpftrg );
               printf( " FILE SRC fexist (d): %d\n", fexist(  ncpfsrc ) );
               printf( " FILE TRG fexist (d): %d\n", fexist(  ncpftrg ) );

            if ( fexist( dp->d_name ) == 1 )
            {
               printf( " FILE SRC:     %s\n", ncpfsrc );
               printf( " FILE TRG:     %s\n", ncpftrg );
               printf( " FILE SRC (d): %d\n", fexist( ncpftrg ) );
               if ( fexist( ncpfsrc ) == 1 )
               {
                  printf( " COPY SRC=>TRG: %s %s\n", ncpfsrc,  ncpftrg );
                  if ( fexist( ncpfsrc ) == 1 )
                  {
                     printf( " NCP Start.\n" );
                     ncp( ncpftrg , ncpfsrc );
                     printf( " NCP End.\n" );
                  }
               }

            }
            printf( "====" );
         }
   }
   closedir( dirp );
}






void nrunwith( char *thecmd , char *thefile )
{
       char cmdi[PATH_MAX];
       char foocwd[PATH_MAX];
       printf( "<RUNWITH DIR:  %s\n",       getcwd( foocwd, PATH_MAX ) );
       printf( " RUNWITH CMD:  %s %s>\n" ,  thecmd , thefile ) ; 
       strncpy( cmdi , "  " , PATH_MAX );
       strncat( cmdi , thecmd , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " \"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , thefile , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "\"" , PATH_MAX - strlen( cmdi ) -1 );
       system( cmdi );
}






///////////////// new
char *fextension(char *str)
{ 
    char ptr[strlen(str)+1];
    int i,j=0;
    //char ptrout[strlen(ptr)+1];  
    char ptrout[25];

    if ( strstr( str, "." ) != 0 )
    {
      for(i=strlen(str)-1 ; str[i] !='.' ; i--)
      {
        if ( str[i] != '.' ) 
            ptr[j++]=str[i];
      } 
      ptr[j]='\0';

      j = 0; 
      for( i=strlen(ptr)-1 ;  i >= 0 ; i--)
            ptrout[j++]=ptr[i];
      ptrout[j]='\0';
    }
    else
     ptrout[0]='\0';

    size_t siz = sizeof ptrout ; 
    char *r = malloc( sizeof ptrout );
    return r ? memcpy(r, ptrout, siz ) : NULL;
}







////////////////////
void nbmr2tex( )
{ 
   printf( " ====\n" );
   printf( " >NBMR2TEX\n" );
   printf( " ====\n" );
   DIR *dirp;
   char mycwd[PATH_MAX];
   char mybmrfile[PATH_MAX];
   struct dirent *dp;
   dirp = opendir( "." );
   while  ((dp = readdir( dirp )) != NULL ) 
   {
         if (  strcmp( dp->d_name, "." ) != 0 )
         if (  strcmp( dp->d_name, ".." ) != 0 )
         if ( ( strcmp( fextension( dp->d_name ) , "mrk" ) == 0 ) || ( strcmp( fextension( dp->d_name ) , "bmr" ) == 0 ))
         {
             printf( " Found either MRK or BMR File.\n");
             printf( " DIR:%s\n",  getcwd( mycwd, PATH_MAX ) );
             printf( " FILE:%s\n", dp->d_name );
             strncpy( mybmrfile , dp->d_name, PATH_MAX );

             printf( "     --PASS1/2--\n" );
             printf( "  PATH:%s\n",  getcwd( mycwd, PATH_MAX ) );

             if ( fexist( mybmrfile ) == 1 )
               nrunwith(  " makebmr ", mybmrfile ); 

              printf( "     --PASS2/2--\n" );

             if ( fexist( mybmrfile ) == 1 )
               nrunwith(  " makebmr ", mybmrfile ); 

             printf( "  PATH:%s\n",  getcwd( mycwd, PATH_MAX ) );
         }
   }
   closedir( dirp );
}









int main( int argc, char *argv[])
{
     char cwd[PATH_MAX];
     char dirarg[PATH_MAX];
     char trgdir[PATH_MAX];
     char srcdir[PATH_MAX];
     char file[PATH_MAX];
     strncpy( pathbefore, getcwd( cwd, PATH_MAX ), PATH_MAX );

     ////////////////////////////////////////////////////////
     if ( argc == 2)
     if ( strcmp( argv[1] , "-t" ) ==  0 ) 
     {
       printf("%d\n", (int)time(NULL));
       return 0;
     }

    if ( argc <= 1)
        return 0;

    strncpy( dirarg, argv[ 1 ] , PATH_MAX );
    printf("===========\n");
    printf("= MKSLIDE =\n");
    printf("===========\n");
    printf(" time: %d\n", (int)time(NULL));
    printf(" PATH: %s\n", pathbefore );
    printf(" ARG: %s\n" , dirarg );
    // new temp
    strncpy( file , getenv( "HOME" ) , PATH_MAX );
    strncat( file , "/" ,              PATH_MAX - strlen( file ) -1 );
    strncat( file , "temp/" ,          PATH_MAX - strlen( file ) -1 );
    printf(" TRG (root): %s\n" , file );
    printf(" fexist...\n");
    if ( fexist( file ) == 2 ) 
       printf( " DIR ~/temp/ already exists.\n");
    else 
    {
       printf( " CREATE DIR ~/temp/.\n");
       nrunwith( " mkdir " , file );
    }
    printf(" dircheck...\n");
    if ( fexist( file ) == 2 ) 
       printf( " DIR ~/temp/ already exists.\n");
    else 
    {
       printf( " CREATE DIR ~/temp/.\n");
       nrunwith( " mkdir " , file );
    }
    // new arg dir temp
    strncpy( file , getenv( "HOME" ) , PATH_MAX );
    strncat( file , "/" ,              PATH_MAX - strlen( file ) -1 );
    strncat( file , "temp/" ,          PATH_MAX - strlen( file ) -1 );
    strncat( file , dirarg  ,          PATH_MAX - strlen( file ) -1 );
    printf(" TRG (dir): %s\n" , file );
    printf(" dircheck...\n");
    if ( dircheck( file ) == 2 ) 
       printf( " EXIST DIR %s\n", file );
    else 
    {
       printf( " CREATE DIR %s\n", file );
       nrunwith( " mkdir " , file );
    }
    strncpy( trgdir , file , PATH_MAX );
    printf(  " Var trgdir, file: %s %s\n", trgdir , file );


    strncpy( file , getcwd( cwd, PATH_MAX ) , PATH_MAX );
    strncat( file , "/" ,            PATH_MAX - strlen( file ) -1 );
    strncat( file , dirarg  ,        PATH_MAX - strlen( file ) -1 );
    strncat( file , "/src/" ,         PATH_MAX - strlen( file ) -1 );
    strncpy( srcdir, file, PATH_MAX );
    printf(" SRCDIR (dir): %s\n" , srcdir );

    strncpy( file , getcwd( cwd, PATH_MAX ) , PATH_MAX );
    strncat( file , "/" ,            PATH_MAX - strlen( file ) -1 );
    strncat( file , dirarg  ,        PATH_MAX - strlen( file ) -1 );
    strncat( file , "/" ,         PATH_MAX - strlen( file ) -1 );
    printf(" dircheck...\n");
    if ( dircheck( file ) == 2 ) 
       printf( " EXIST DIR %s\n", file );
    else 
    {
       printf( " CREATE DIR %s\n", file );
       nrunwith( " mkdir " , file );
    }


    strncpy( file , getcwd( cwd, PATH_MAX ) , PATH_MAX );
    strncat( file , "/" ,            PATH_MAX - strlen( file ) -1 );
    strncat( file , dirarg  ,        PATH_MAX - strlen( file ) -1 );
    strncat( file , "/src/" ,         PATH_MAX - strlen( file ) -1 );
    printf(" dircheck...\n");
    if ( dircheck( file ) == 2 ) 
       printf( " EXIST DIR %s\n", file );
    else 
    {
       printf( " CREATE DIR %s\n", file );
       nrunwith( " mkdir " , file );
    }

    chdir( pathbefore ); 
    chdir( srcdir ); 
    strncpy( file , getcwd( cwd, PATH_MAX ) , PATH_MAX );

    printf( "DIR: %s\n" , file );
    printf( "===LS1===\n");
      nls();
    printf( "===LS1===\n");
      printdir();
    printf( "===START NCP===\n");
    ncpbmr(  trgdir, srcdir );
    printf( "===END NCP===\n");

    printf( "===TEX===\n");
    chdir( pathbefore ); 
    chdir( trgdir ); 
    if ( dircheck( trgdir ) == 2 ) 
    {
      printf( "DIR FOUND %s\n", trgdir );
      nbmr2tex( );
    }
    chdir( pathbefore ); 

    printf( "=-=-=-=\n");
    printf( "SRCDIR\n");
    chdir( srcdir ); 
    nls();
    printf( "=-=-=-=\n");
    printf( "TRGDIR\n");
    chdir( trgdir ); 
    nls();
    printf( "=-=-=-=\n");

    chdir( pathbefore ); 
    printf( "==COMPLETED==\n");

    return 0;
}


