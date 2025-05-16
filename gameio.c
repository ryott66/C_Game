/*****************************************************************************/
/*!	@file	gameio.c
    @brief	IO settings and control functions for console game programming

    IO setting for console changes based on OS type (Win&Mac)

    @see	gameio.h　Header file for gameio.c
    @par	Log
        - 2020/11/30 Ver. 1.0
            - Basic settings were programmed (by Keisuke SHIMA)
         - 2020/12/01 Ver. 1.1
            - Change initialSettingGameIO for automatically setting (by Keisuke SHIMA)
            - Use global variable (gbl or Gbl) for working path of music.<BR>
              playSound() function can be used for playing music instead of PLAY_SOUND().
   @attention
        -
    @par Copyright
        Copyright &copy; 2013- Keisuke SHIMA All rights reserved.
******************************************************************************/
#include "gameio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//For Windows-------------------------------------------
#ifdef _WIN32

///////////////////////////////////////////
void timeSleep(int msec)
{
    Sleep((unsigned long)msec);
}

///////////////////////////////////////////
int initialSettingGameIO( void )
{
    enable_virtual_terminal_processing(stdout);

    return initialSettingPathGameIO(GAMEIO_FILENAME);
}

///////////////////////////////////////////
BOOL enable_virtual_terminal_processing(FILE* stream)
{
    HANDLE handle = (HANDLE)_get_osfhandle(_fileno(stream));
    DWORD mode = 0;
    if (!GetConsoleMode(handle, &mode)) {
        return FALSE;
    }
    if (!SetConsoleMode(handle, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
        return FALSE;
    }
    return TRUE;
}
///////////////////////////////////////////
int getUserName(char name[], int size)
{
    TCHAR szUserName[UNLEN + 1];
    DWORD dwUNLen = UNLEN;

    if (!GetUserName((LPTSTR)szUserName, &dwUNLen)) {
        printf("Error: %u", GetLastError());
        return 1;
    }
    //_tprintf(TEXT("Username: %s\n"), szUserName);

    wcstombs(name, (wchar_t*)szUserName, size);
    return 0;
}

///////////////////////////////////////////
int playSound(char fname[])
{
    char tmp[STR_MAX];
    int retVal = -1;
    if (isGblWorkPath) {
        sprintf(tmp, "%s%s%s", gblWorkPath, PATH_SLASH, fname);
        // printf("Global=%s\n", tmp); //for debug

        sndPlaySound(tmp, SND_ASYNC | SND_LOOP);
        retVal = 0;
    } 
    else {
        retVal = -1;
    }
    return retVal;
}


///////////////////////////////////////////
void stopSound(void)
{
    sndPlaySound(NULL, SND_ASYNC);
}

//For MacOS-------------------------------------------
#elif __MACH__
#include <unistd.h>

///////////////////////////////////////////
void timeSleep(int msec)
{
    unsigned long tmp = (unsigned long)msec * 1000;  //Convert to micro sec from msec
    
    usleep((unsigned int)tmp);
}

///////////////////////////////////////////
int playSound( char fname[] )
{
    char tmp[STR_MAX];
    sprintf(tmp,"afplay %s%s&",gblWorkPath, fname);
    //printf("Music: %s\n",tmp);
    system(tmp);
    
    return 0;
}

///////////////////////////////////////////
void stopSound( void )
{
    system("killall afplay");
}

///////////////////////////////////////////
int initialSettingGameIO( void )
{
/*    int retVal = -1;
    char tmp[STR_MAX];
    FILE* fp = NULL;
    char fname[STR_MAX];

    sprintf(tmp, "%s%sUsers%s%s%sDocuments%s%s", PATH_DRIVE, PATH_SLASH, PATH_SLASH, getlogin(), PATH_SLASH, PATH_SLASH, GAMEIO_FILEPATH);
    mkdir(tmp, 0755);
    chdir(tmp);
    //getcwd(tmp,STR_MAX); //for debug
    //printf("%s\n",tmp);
    retVal = changeCDirToWork(pathName);

    return retVal;
*/  
    return initialSettingPathGameIO(GAMEIO_FILENAME);
}

///////////////////////////////////////////
int getUserName(char name[], int size)
{
    strcpy(name, getlogin());

    return 0;
}

#endif

//! Global path for working folder (music etc)
char gblWorkPath[STR_MAX] = "";

//! Global flag for working folder
//! set=1
int isGblWorkPath = 0;

///////////////////////////////////////////
int changeCDirToWork( char pathName[] )
{
    int retVal=-10;
    char tmp[STR_MAX];
    FILE *fp=NULL;
    char fname[STR_MAX];
    
    int countCode=0;
    if( (fp=fopen(pathName,"r"))!=NULL     ){
        for( countCode=0; fscanf(fp,"%s",tmp)!=EOF; countCode++){
            if(strncmp(tmp,OS_CODE,OS_CODENUM)==0){
                strncpy(fname,&tmp[OS_CODENUM],STR_MAX-OS_CODENUM);
                chdir(fname);
                //printf("%s\n",fname); //for debug
                retVal=0;
            } else{
                retVal=-2;
            }
        }
    } else{ //NR
        retVal=-1;
    }
    
    return retVal;
}

///////////////////////////////////////////
int getWorkingDirPath(char pathName[])
{
    int retVal = -10;
    char tmp[STR_MAX];
    FILE* fp = NULL;
//    char fname[STR_MAX];

    int countCode = 0;
    if ((fp = fopen(pathName, "r")) != NULL) {
        for (countCode = 0; fscanf(fp, "%s", tmp) != EOF; countCode++) {
            if (strncmp(tmp, OS_CODE, OS_CODENUM) == 0) {
                strncpy(gblWorkPath, &tmp[OS_CODENUM], STR_MAX - OS_CODENUM);
                isGblWorkPath = 1;  //setup flag
                //Directory change is bad for other application. no use
                //chdir(fname);
                //printf("GLOBAL=%s\n", gblWorkPath); //for debug
                retVal = 0;
            }
            else {
                retVal = -2;
            }
        }
    }
    else { //NR
        retVal = -1;
    }

    return retVal;
}

///////////////////////////////////////////
int initialSettingPathGameIO(char pathName[])
{
    int retVal = -1;
    char tmp[STR_MAX];
    char pname[STR_MAX];

    getUserName(tmp, STR_MAX);
    sprintf(pname, "%s%sUsers%s%s%sDocuments%s%s", PATH_DRIVE, PATH_SLASH, PATH_SLASH, tmp, PATH_SLASH, PATH_SLASH, GAMEIO_FILEPATH);
    //printf("Path: %s", pname); //for debug
    mkdir(pname);
    //chdir(pname);
    sprintf(tmp, "%s%s%s", pname, PATH_SLASH, pathName);
//    printf("Path: %s\n", tmp); //for debug
    //getcwd(pname,STR_MAX); //for debug
//    printf("%s\n",pname);
    
    //Directory change is bad for other application. no use
    retVal = changeCDirToWork(tmp);
    retVal = getWorkingDirPath(tmp);
    return retVal;

}
