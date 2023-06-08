NAME = micro_paint


SRCS = micro_paint.c


OBJ = ${SRCS:.c=.o}


CC = cc


FLAG = -Wall -Werror -Wextra 


%.o : %.c
	@${CC} ${FLAG} -c $< -o $@
	@echo "compiling..."


${NAME} : ${OBJ}
	@${CC} ${FLAG} ${OBJ} -o ${NAME}
	@echo "${NAME} ready."


all : ${NAME}


clean :
	@rm -rf ${OBJ}
	@echo "OBJS deleted."


fclean : clean
	@rm -rf ${NAME}
	@echo "${NAME} deleted."


re : fclean all clean


.PHONY : clean fclean all re
