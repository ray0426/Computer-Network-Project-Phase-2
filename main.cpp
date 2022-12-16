#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sstream>
#include <string>
using namespace std;
#define PORT 8000
#define HOST "0.0.0.0"
#define BUFF_MAX 1024

enum FileType {
	HTML,
	CSS,
	PNG,
	JPEG,
	JS,
	XCON,
	GIF
};

int request_handler(int new_socket, char* request);
int send_response(int new_socket, char* send_buffer, int datalen);

int main(void)
{
	int opt = 1; // for setsockopt
	int pid, recvstat;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	int new_socket, valread;
	
	char recv_buffer[BUFF_MAX] = { 0 };
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		cout << "Fail to create a socket." << endl;
		exit(1);
	} else {
		cout << "Create a socket success." << endl;
	}

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	bind(sockfd, (struct sockaddr*)&address, sizeof(address));

	listen(sockfd, 20);

	while (new_socket = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) {
		// cout << "accepted" << endl;
		if ((pid = fork()) < 0) {
			// fork error
			cout << "fork error" << endl;
			exit(1);
		}
		if (pid == 0) {
			// inside child process
			cout << "start child process" << endl;
			if (close(sockfd) != 0) {
				cout << "close sockfd in child error" << endl;
				// exit(1);
			}
			if ((recvstat = recv(new_socket, recv_buffer, BUFF_MAX, 0)) < 0) {
				cout << "recv error" << endl;
				// exit(1);
			}
			cout << "recived " << recvstat << "bytes" << endl;
			cout << "request: " << endl;
			cout << "===============================================" << endl;
			cout << recv_buffer << endl;
			cout << "===============================================" << endl;
			request_handler(new_socket, recv_buffer); // TODO
			
			if (close(new_socket) != 0) {
				cout << "close new socket in child error" << endl;
				// exit(1);
			}
			cout << "close child process" << endl;
			exit(0);
		} else {
			// pid > 0, inside parent process
			if (close(new_socket) != 0) {
				cout << "close new socket in child error" << endl;
				// exit(1);
			}
		}
	}

	return 0;
}

int request_handler(int new_socket, char* request)
{
	FILE *fp;
	char send_buffer[BUFF_MAX], buffer1[100];
	long int f_size;
	int size, nmemb;
	const char* d = " ";
	char *method, *target, *http_version;
	char *headerline, *bodyline;
	FileType ftype;
	int register_status, login_status;

	// TODO extrate the file to be sent and calculate the length
	method = strtok(request, d);
	cout << "method: " << method << endl;
	target = strtok(NULL, d);
	cout << "target: "<< target << endl;
	http_version = strtok(NULL, "\n");
	cout << "http_version: "<< http_version << endl;

	if (strcmp(method, "GET") == 0) {
		if (strcmp(target, "/") == 0) {
			fp = fopen("index.html", "r");
			fseek(fp, 0L, SEEK_END);
			f_size = ftell(fp);
			// fseek(fp, SEEK_SET, 0);
			rewind(fp);
			ftype = HTML;
		} else if (strcmp(target, "/login") == 0) {
			fp = fopen("login.html", "r");
			fseek(fp, 0L, SEEK_END);
			f_size = ftell(fp);
			// fseek(fp, SEEK_SET, 0);
			rewind(fp);
			ftype = HTML;
		} else if (strcmp(target, "/favicon.ico") == 0) {
			fp = fopen("favicon.ico", "r");
			fseek(fp, 0L, SEEK_END);
			f_size = ftell(fp);
			// fseek(fp, SEEK_SET, 0);
			rewind(fp);
			ftype = XCON;
		}
	} else if (strcmp(method, "POST") == 0) {
		if (strcmp(target, "/login") == 0) {
			while ((headerline = strtok(NULL, "\n")) && headerline[0] != '\r') {
				// cout << "headerline: "<< headerline << endl;
				continue;
			}
			bodyline = strtok(NULL, "\n");
			cout << "bodyline: "<< bodyline << endl;
			istringstream input_stream(bodyline);
			string key;
			string value;
			string username, password;
			while (getline(input_stream, key, '=')) {
				getline(input_stream, value, '&');
				if (key == "username") {
					username = value;
				} else if (key == "password") {
					password = value;
				}
			}
			cout << "username: " << username << endl;
			cout << "password: " << password << endl;
			login_status = login(username, password);
			// fp = fopen("index.html", "r");
			// fseek(fp, 0L, SEEK_END);
			// f_size = ftell(fp);
			// // fseek(fp, SEEK_SET, 0);
			// rewind(fp);
			// ftype = HTML;
		}
	}

	strcpy(send_buffer, "HTTP/1.1 200 OK\r\n");
	strcat(send_buffer, "Cache-control: public, max-age=0\r\n");
	sprintf(buffer1, "Content-Length: %ld\r\n", f_size);
	strcat(send_buffer, buffer1);
	switch (ftype) {
		case HTML:
			strcat(send_buffer, "Content-type: text/html; charset=UTF-8\r\n");
			break;
		case XCON:
			strcat(send_buffer, "Content-type: image/x-icon\r\n");
			break;
		case JPEG:
			strcat(send_buffer, "Content-type: image/jpeg\r\n");
			break;
		case PNG:
			strcat(send_buffer, "Content-type: image/png\r\n");
			break;
		case JS:
			strcat(send_buffer, "Content-type: application/javascript\r\n");
			break;
		case CSS:
			strcat(send_buffer, "Content-Type: text/css; charset=utf-8\r\n");
			break;
		case GIF:
			strcat(send_buffer, "Content-Type: image/gif\r\n");
			break;
		default:
			strcat(send_buffer, "Content-Type: type error\r\n");
	}
	strcat(send_buffer, "\r\n");

	send_response(new_socket, send_buffer, strlen(send_buffer));

	size = sizeof(char); // 1
	nmemb = BUFF_MAX - 1; // sizeof(send_buffer)
	
	while (f_size > 0) {
		f_size -= fread(send_buffer, size, nmemb, fp);
		// cout << send_buffer << endl;
		send_response(new_socket, send_buffer, strlen(send_buffer));
	}
	return 0;
}

int send_response(int new_socket, char* send_buffer, int datalen)
{
	int sent = 0;
	cout << "start sending" << endl;
	while (datalen > 0) {
		sent = send(new_socket, send_buffer, datalen, 0);
		if (send < 0) {
			cout << "send error" << endl;
			return -1;
		}
		if (send == 0) {
			cout << "client has disconnected" << endl;
			return -1;
		}
		send_buffer += sent;
		datalen -= sent;
		cout << sent << " bytes sent" << endl;
	}
	cout << "===============================================" << endl;
	return 0;
}

int login(string username, string password)
{
	
}