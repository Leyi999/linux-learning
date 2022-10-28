all: penv-d out-s out-d#默认生成所有文件
dynamic:myadd_d.o mysub_d.o
myadd_d.o: myadd.c 
	gcc -fPIC -c $^ -o $@
mysub_d.o: mysub.c
	gcc -fPIC -c $^ -o $@
static: myadd_s.o mysub_s.o
myadd_s.o:myadd.c
	gcc -c $^ -o $@
mysub_s.o:mysub.c
	gcc -c $^ -o $@
.PHONY:clean-c #保留库和源码
clean-c:
	rm -rf *.o *.out 
.PHONY:lib-s#生成静态库
lib-s:lib_s

lib_s: static mymath.h#依赖普通.o以及头文件
	mkdir lib_s 
	mkdir lib_s/lib
	mkdir lib_s/header
	cp mymath.h lib_s/header
	ar -rc lib_s/lib/libmymath.a myadd_s.o mysub_s.o
.PHONY:lib-d#生成动态库
lib-d:lib_d 

lib_d: dynamic mymath.h#依赖PIC的.o以及头文件
	mkdir lib_d
	mkdir lib_d/lib 
	mkdir lib_d/header
	cp mymath.h lib_d/header
	gcc  myadd_d.o mysub_d.o -shared -o lib_d/lib/libmymath.so
.PHONY:out-s #使用静态库链接
out-s: static lib_s test.c
	gcc test.c -o test_s.out -I./lib_s/header/ -L./lib_s/lib/ -lmymath #要告诉编译器头文件去和链接库去哪里找 -l去掉前缀和后缀的库名
.PHONY:out-d #使用动态库链接
out-d: dynamic lib_d test.c
	gcc test.c -o test_d.out -I./lib_d/header/ -L./lib_d/lib/ -lmymath
.PHONY:penv-d#添加动态库环境变量 除此之外还有在系统路径下添加软硬链接 配置文件等方法 但是都需要超级用户权限
penv-d:lib_d 
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:/home/hly/linux-learningcode/动静态库/lib_d/lib
.PHONY:clean#只保留源码
clean:
	rm -rf  lib* *.o *.a* *.so *.out
	
