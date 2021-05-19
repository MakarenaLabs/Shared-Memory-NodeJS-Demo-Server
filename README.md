# How to write/read to/from shared memory with NodeJS

With this repo you can create a simple server to write/read to/from shared memory through two dedicated APIs.

## Prerequisites
The prerequisites are:
 - `NodeJS` with `npm` and `node-gyp`
 - `C++`

## Building node module
First of all, you have to build the custom node module in order to use it. So, go to `shmnode` directory and launch two simple `node-gyp` commands.

From the root directory of the repo, launch these commands:
```bash
cd shmnode
node-gyp configure --debug
node-gyp build --debug
```

If the output of the terminal is like this
```bash
gyp info it worked if it ends with ok
gyp info using node-gyp@6.1.0
gyp info using node@10.19.0 | linux | x64
...
gyp info ok
```

after `node-gyp configure --debug` and

```bash
gyp info it worked if it ends with ok
gyp info using node-gyp@6.1.0
gyp info using node@10.19.0 | linux | x64
gyp info spawn make
...
gyp info ok
```
your build is succesfull and you can start using this custom module.

Now you can return to the root directory of the repo.

## Starting server
Once you have built the node module, you have to install some packages in order to start the simple server.
So, go to the root directory of the repo and install node packages with:
```bash
npm install
```

After that, if the installation ends without errors, you can easily start the server with:
```bash
node server.js
```

The server is listening on port `8080` by default and you can use its APIs. If the node command ends without errors, you should have this in output (node listening on selected port):
```bash
user@user-vm:~/path/to/repo$ node server.js 
listening on *:8080
|
```

## Server routes
In this section server routes are provided.

### **Read from shared memory**
----
  Returns json data read from shared memory.

|       Title      	|           Shared memory data           	|
|:----------------:	|:--------------------------------------:	|
|        **URL**       	|                  `/read`                 	|
|      **Method**      	|                   `GET`                  	|
|  **URL Parameters**  	|                  None                  	|
| **Success Response** 	| Code: `200`<br>Content: `{"TEST": "test"}` 	|

### **Write to shared memory**
----
  Returns json data wrote and read from shared memory.

|       Title      	|                Shared memory data                	|
|:----------------:	|:------------------------------------------------:	|
|        **URL**       	|                      `/write`                      	|
|      **Method**      	|                       `POST`                       	|
|  **URL Parameters**  	|                       None                       	|
|       **Body**       	| type: `application/json`<br>data: `{"TEST": "test"}` 	|
| **Success Response** 	|      Code: `200`<br>Content: `{"TEST": "test"}`      	|

## Credits
[Staff Makarenalabs](mailto:staff@makarenalabs.com)