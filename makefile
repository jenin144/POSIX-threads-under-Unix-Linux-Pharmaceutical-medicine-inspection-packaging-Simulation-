G = gcc -g
O = -o
names = main timer
thread_args = -lpthread -lrt

files:
	$(G) main.c $(O) main $(thread_args)
	$(G) liquid.c $(O) liquid $(thread_args)
	$(G) pill.c $(O) pill $(thread_args)
	$(G) gl.c $(O) gl -lglut -lGLU -lGL -lm $(thread_args)


clean:
	rm -f $(names)
