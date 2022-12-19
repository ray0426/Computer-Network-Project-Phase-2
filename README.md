# Computer Network Project Phase 2
## About
This project is about a simple implementation of HTTP server which can host a profile page. Clients can easily browse it by simply entering the ip address on the web browsers, including `Chrome`, `Edge` and `FireFox`.  ( Do not support `Safari`)\
GitHub Repository URL: [https://github.com/ray0426/Tic-tac-toe](https://github.com/ray0426/Tic-tac-toe) 

## Our Project IP Adderss
Our project is deloyed on the below ip address.

```
http://60.251.128.233:48763
```

## Compilation and Execution
### Step 0
Make sure that you are under the directory of our project. 

### Step 1
Modify the `HOST` address and `PORT` number in line 13 and 14 in `main.cpp`.

```c++
#define PORT 8000
#define HOST "0.0.0.0"
```

### Step 2
Compile and run the server. Run below commands on your terminal. 

```bash
$ g++ main.cpp
$ ./a.out
```

### Step 3
Open your web browser and enter your ip address and port number on `Chrome`, `Edge` or `FireFox`. Then you can browse the webpage. 

## Demo
This is what our page look like.

[Demo Video](https://drive.google.com/file/d/15lyMjopYzNLPRqalIy9j1eI02Aun5lDj/preview "Demo Video")

## File Structure
### Server
The following file is about the server. 

```bash
CN_Project_Phase2
└─── main.cpp	// the server
```

### Profile Page
The following files are about the profile page.

```bash
CN_Project_Phase2
├─── index.html	    // html
├─── board.html     // html
├─── file.html      // html
├─── profile.css	// css
├─── laybkgnd.gif	// background
├─── 346496.jpg		// my photo
├─── intro.mp4          // video
└─── librispeech.flac   // sound
```


## Implemented Functions

### Message Board (留言板)
- Visitors can turn to the message board page and type in their name and message, then their messeage will show on the page with time stamp. 
- We implement the response of `POST` request in our server, so that it can deal with the input meaasge from visitors.   
- **Restriction: Can only enter english alpabet and numbers.**

### Video Streaming (影片串流)
- Autoplaying the video provided by the website.
- Our server provides the `GET` request of multiple types of files from clients, including `.html`, `.css`, `.gif`, `.jpg`, `.mp4` and `.flac`. 
- **Restriction: Cannot pull the video progress bar on `Chrome` and `Edge`.**

### Sound Streaming (聲音串流)
- Autoplaying the sound provided by the website.
- Our server provides the `GET` request of multiple types of files from clients, including `.html`, `.css`, `.gif`, `.jpg`, `.mp4` and `.flac`. 
- **Restriction: Cannot pull the sound progress bar on `Chrome` and `Edge`.**

## Contributors

* B08901211 電機四 游耿睿
* B08901215 電機四 蕭淇元
