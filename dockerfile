FROM ubuntu
COPY lab3.cpp .
RUN apt-get update && apt-get install gcc gcc-multilib g++ -y
RUN gcc -fno-pie -no-pie lab3.cpp -o lab3 -g -lstdc++
CMD ./lab3