OUT := ../bin/main
SRCS :=	$(wildcard *.cpp) #将当前目录下的所有.cpp文件的文件名以空格分割，然后赋值给SRCS变量
OBJS :=	$(patsubst %.cpp,%.o,$(SRCS)) #获取当前目录下所有.cpp文件对应的.o文件，以空格分割             
COM_OP := -std=c++17 -Wall -g 
LDFLAGS = -lpthread

$(OUT):$(OBJS)
	g++ $^ -o $@
%.o : %.cpp
	g++ -c $< $(COM_OP)
.PHONY: clean rebuild
clean:
	rm -f $(OUT) $(OBJS)         
rebuild: clean main                                                                              
