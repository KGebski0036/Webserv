BASE		=	\033[38;5;
RED			=	\033[38;5;196m
RED_B		=	\033[48;5;160m
GREEN		=	\033[38;5;40m
GREEN_B		=	\033[48;5;40m
COMPILATION	=	\033[48;5;40m[COMPILATION]\033[0m $(GREEN)
BLUE		=	\033[38;5;123m
BLUE_B		=	\033[48;5;39m
INFO		=	\033[48;5;39m[INFORMATION]\033[0m $(BLUE)
TESTING_B	=	\033[48;5;202m[ TESTING MODE IS NOW ACTIVATED ]\033[0m
TESTING_T	=	\033[38;5;202m
RESET		=	\033[0m
BOLD		=	\033[1m
ITALIC		=	\033[3m
UNDERLINE	=	\033[4m
STRIKE		=	\033[9m

CURRENT_PROGRESS = 0
TOTAL_PROGRESS = $(words $(OBJ))
ifeq ($(shell uname), Linux)
	PROGRESS_WIDTH = 62
	OS			=	Linux
	PROGRESS_DONE_CHAR = \#
	PROGRESS_TODO_CHAR = -
else
	PROGRESS_WIDTH = 33
	OS				=	Mac
	PROGRESS_DONE_CHAR = 🟩
	PROGRESS_TODO_CHAR = ⬜️
endif

NAME		=	webserv
CC			=	c++
CPP_FLAGS	=	-Wall -Wextra -Werror -std=c++98 --pedantic-errors -g 
# -fsanitize=address -pthread
#-g

HDRS_DIR	=	./inc/
OBJ_DIR		=	./obj
SRC_DIR		=	./src

SRC			=	$(shell find $(SRC_DIR) -name '*.cpp')
HDRS 		=	-I$(HDRS_DIR)

OBJ			=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

all: ascii-art $(NAME)

$(NAME): $(OBJ)
	@echo "$(COMPILATION)ᯤ  $(NAME) compilation:"
	$(CC) $(CPP_FLAGS) $(HDRS) $(OBJ) -o $(NAME)
	@echo "$(RESET)$(INFO)ᯤ  $@ executable has been created$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	@$(CC) $(CPP_FLAGS) $(HDRS) -c $^ -o $@
	$(eval CURRENT_PROGRESS=$(shell echo $$(($(CURRENT_PROGRESS)+1))))
	$(eval PERCENTAGE=$(shell echo $$(($(CURRENT_PROGRESS)*100/$(TOTAL_PROGRESS)))))
	@if [ $(CURRENT_PROGRESS) -eq $(TOTAL_PROGRESS) ]; then \
		printf "\033[2A\r\033[K$(GREEN_B)[COMPILATION]$(RESET) \033[38;5;40m$(PERCENTAGE)%% [$$(printf '%*s' $$(($(CURRENT_PROGRESS)*$(PROGRESS_WIDTH)/$(TOTAL_PROGRESS))) | tr ' ' '$(PROGRESS_DONE_CHAR)')$$(printf '%*s' $$(($(PROGRESS_WIDTH)-($(CURRENT_PROGRESS)*$(PROGRESS_WIDTH)/$(TOTAL_PROGRESS)))) | tr ' ' '$(PROGRESS_TODO_CHAR)')] $<\033[0m ✅$(RESET)\n"; \
	else \
		printf "\033[2A\r\033[K$(GREEN_B)[COMPILATION]$(RESET) \033[38;5;51m$(PERCENTAGE)%% [$$(printf '%*s' $$(($(CURRENT_PROGRESS)*$(PROGRESS_WIDTH)/$(TOTAL_PROGRESS))) | tr ' ' '$(PROGRESS_DONE_CHAR)')$$(printf '%*s' $$(($(PROGRESS_WIDTH)-($(CURRENT_PROGRESS)*$(PROGRESS_WIDTH)/$(TOTAL_PROGRESS)))) | tr ' ' '$(PROGRESS_TODO_CHAR)')] $<$(RESET)\n\n"; \
	fi
	@sleep 0.01

clean:
	@for obj in $(OBJ); do \
		rm -f $$obj; \
		printf "$(RED_B)[DELETED]$(RESET) $(RED)$$obj$(RESET)\n"; \
	done

fclean: clean
	@rm -f $(NAME);
	@rm -rf $(OBJ_DIR);
	@printf "$(RED_B)[DELETED]$(RESET) $(RED)$(NAME)$(RESET)\n"; \

re: fclean all

ascii-art:
	@clear
	@echo "$(BASE)231m .                                                                                                   -=━━━┓"
	@echo "$(BASE)231m | ⠀⠀⠀⠀⠀⠀⠀⣀⣤⣶⣿⠷⠾⠛⠛⠛⠛⠷⠶⢶⣶⣤⣄⡀⠀⠀⠀⠀⠀⠀                                                                       ◹ ┃"   
	@echo "$(BASE)195m ┃ ⠀⠀⠀⠀⣀⣴⡾⠛⠉⠁⠀          ⠀⠉⠛⠿⣷⣄⡀⠀⠀⠀                                                                        |"
	@echo "$(BASE)195m ┃ ⠀⠀⣠⣾⠟⠁⠀⠀⠀⠀⠀          ⠀⠀⠀⠀⠈⠛⢿⣦⡀⠀                                                                        '"   
	@echo "$(BASE)195m ┃ ⢠⣼⠟⠁⠀⠀⠀⠀⣠⣴⣶⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣄⠀⠀⠀  ⠀⠙⣧⡀    "
	@echo "$(BASE)195m ┃ ⣿⡇⠀⠀⠀⢀⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀ ▁▁▁▁▁ ▁▁▁▁▁▁▁▁            ▁▁      ▁▁      ▁▁▁."
	@echo "$(BASE)195m ┃ ⣿⣿⣦⡀⣠⣾⣿⣿⣿⡿⠟⠛⠁⠁⠁⠁⠁⠁⠛⠻⢿⣿⣿⣿⣿╱  │  │╲▁▁▁▁▁  ╲          ╱  ╲    ╱  ╲ ▁▁▁▁╲▁ │▁▁   ▁▁▁▁▁▁ ▁▁▁▁▁▁▁▁▁▁▁▁▁▁"
	@echo "$(BASE)195m ┃ ⠉⠻⣿⣿⣿⣿⣿⡿⠋⠀⠀          ⠀⢿⣿╱   │  │▁╱  ▁▁▁▁╱   ▁▁▁▁▁▁ ╲   ╲╱╲╱   ╱╱ ▁▁ ╲│ ▁▁ ╲ ╱  ▁▁▁╱╱ ▁▁ ╲▁  ▁▁ ╲  ╲╱ ╱"
	@echo "$(BASE)195m ┃ ⠀⠀⠈⠙⠛⣿⣿⠀⠀⠀⠀            ╱    ^   ╱       ╲  ╱▁▁▁▁▁╱  ╲        ╱╲  ▁▁▁╱│ ╲▁╲ ╲╲▁▁▁ ╲╲  ▁▁▁╱│  │ ╲╱╲   ╱"
	@echo "$(BASE)195m ┃ ⠀⠀⠀⠀⠀⢿⣿⣷⣄⣀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣷⣀⣀⣾╲▁▁▁▁   │╲▁▁▁▁▁▁▁ ╲           ╲▁▁╱╲  ╱  ╲▁▁▁  >▁▁▁  ╱▁▁▁▁  >╲▁▁▁  >▁▁│    ╲▁╱"
	@echo "$(BASE)195m ┃ ⠀⠀⠀⠀⠀⠈⠻⢿⣿⣿⣿⣿⣿⠟⠛⠛⠻⣿⣿⣿⣿⣿⡿     │▁▁│        ╲╱                ╲╱       ╲╱    ╲╱     ╲╱     ╲╱"
	@echo "$(BASE)195m ┃ ⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠁⣿⡇⠀⠀⠀⠀⢸⣿⡏⠙⠋⠁⠀⠀⠀⠀⠀⠀⠀                                                                        "
	@echo "$(BASE)195m ┃ ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣷⣄⠀⠀⣀⣾⣿⡇⠀⠀⠀⠀⠀                                                                            ▵ "
	@echo "$(BASE)159m ┃ ◺⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                                       ▿┃"
	@echo "$(BASE)159m ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[$(ITALIC)Made with ♥  by @cjackows @kgebski @gskrasti$(RESET)$(BASE)159m]━━━━━━━━━━━━━━━━┛$(RESET)"; echo; echo; echo;
                        

.PHONY: all clean fclean re webserv