#include <v8.h>
#include <node.h>
#include <node_buffer.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <cstring>

#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

using namespace v8;
using namespace std;

const char *sem_fn = "my_sem";
sem_t *semdes;

const int SHM_KEY = 32140895;
const int SHM_SIZE = 2048;
int SHM_ID = -1;

void WriteSHM(const FunctionCallbackInfo<Value> &args){

    Local<Object> bufferObj = args[0].As<Object>();
    uint8_t* dataBuffer = (uint8_t*) node::Buffer::Data(bufferObj);
    size_t bufferLength = node::Buffer::Length(bufferObj);

    semdes = sem_open(sem_fn, O_CREAT, 0644, 0);

    if ( (SHM_ID = shmget(SHM_KEY, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    char* shm = (char*) shmat(SHM_ID,(void*)0,0);

    for(int i = 0; i < (int)bufferLength; i++)
        shm[i] = dataBuffer[i];

    for(int i = (int)bufferLength; i < SHM_SIZE; i++)
        shm[i] = '\0';

    shmdt(shm);

    sem_post(semdes);

}

void ReadSHM(const FunctionCallbackInfo<Value> &args){

    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    semdes = sem_open(sem_fn, O_CREAT, 0644, 0);

    if ( (SHM_ID = shmget(SHM_KEY, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    char* shm = (char*) shmat(SHM_ID,(void*)0,0);

    args.GetReturnValue().Set(String::NewFromUtf8(isolate, shm));

    sem_post(semdes);

}

void init(Handle<Object> exports)
{
    NODE_SET_METHOD(exports, "read", ReadSHM);
    NODE_SET_METHOD(exports, "write", WriteSHM);
}

NODE_MODULE(shmnode, init)

