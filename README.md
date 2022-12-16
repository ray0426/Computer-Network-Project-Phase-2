# HTTP Server
## About
This project is about a simple implementation of HTTP server. The main purpose of the server is to host my own profile page. Clients can easily browse my profile by simply entering the ip address on the web browsers, such as Chrome, Safari or FireFox. 

## Usage
### Step 0
Make sure that you are under the directory of `phase1`, whilch is about my project. 

### Step 1
Modify the ip address and port number in line 17 and 18 in `http-server.c`.

```c
#define ADDRESS "60.251.128.233"
#define PORT 48763
```

### Step 2
Compile and run the server. Run below commands on your terminal. 

```bash
$ gcc http-server.c -o http-server
$ ./http-server
```

### Step 3
Open your web browser and check the page by entering your ip address and port number. `Chrome`, `Safari` and `FireFox` are tested OK. The example is like: 

```
60.251.128.233:48763
```

## Demo
My profile page has been launched on the following ip address, which is a NAS of my colleague, 游耿睿 Ray.


```
60.251.128.233:48763
```
This is what my page look like.

![image](./demo.png)

## Architecture
### Server
The following file is about the server. 

```bash
phase1
└─── http-server.c	// the server
```

### Profile Page
The following files are about the profile page.

```bash
phase1
├─── profile.html	// html
├─── profile.css	// css
├─── laybkgnd.gif	// background
└─── 346496.jpg		// my photo
```


## Function
In this project, the http server provides the `GET` request of some types of files from clients, including `.html`, `.css`, `.gif` and `.jpg`.
