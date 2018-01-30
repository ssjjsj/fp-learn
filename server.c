#include <pthread.h>
#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdlib.h>

#define NUM_THREADS 2
lua_State *mainState;
lua_State *runThread;
pthread_mutex_t count_mutex;
pthread_cond_t count_threshold_cv;

void* thread1(void *threadid)
{
    pthread_mutex_lock(&count_mutex);
    mainState = luaL_newstate();
    luaL_openlibs(mainState);
    runThread = lua_newthread(mainState);
    int status = luaL_loadfile(runThread, "script.lua");
    if (status)
    {
        fprintf(stderr, "load lua file failed %s", lua_tostring(runThread, -1));
    }
    else
    {
        //lua_getglobal(runThread, "main");
        int result = lua_resume(runThread, mainState, 0);
        fprintf(stderr, "run in thread1 result:%d\n", result);
        if (result == LUA_YIELD)
        {
            pthread_cond_signal(&count_threshold_cv);
        }
        else
        {
            if (result != LUA_OK)
            {
                 fprintf(stderr, "run error in thread1:%s\n", lua_tostring(runThread, -1));   
            }
        }
    }
    pthread_mutex_unlock(&count_mutex);
}


void* thread2(void *threadid)
{
    pthread_mutex_lock(&count_mutex);
    pthread_cond_wait(&count_threshold_cv, &count_mutex);
    int result = lua_resume(runThread, mainState, 0);
    fprintf(stderr, "run in thread2 result:%d\n", result);
    pthread_mutex_unlock(&count_mutex);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc, t;
    int num = 0;
    pthread_create(&threads[0], NULL, thread1, (void *)&num);
    pthread_create(&threads[1], NULL, thread2, (void *)&num);

    for (int i=0; i<NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
}