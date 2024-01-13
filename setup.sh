TICK="✓"
BGRN="\033[1;32m"
GRN="\033[0;32m"
RESET="\033[0m"
YELLOW="\033[1;33m"
DEF="\033[0m"

brew_install()
{
    sleep 1
    printf "\r${YELLOW} Brew Installing ${RESET}\n${DEF}"
    git clone --depth=1 https://github.com/Homebrew/brew $HOME/goinfre/.brew
    echo "export PATH=$HOME/goinfre/.brew/bin:$PATH" >> $HOME/.zshrc
    source $HOME/.zshrc
    printf "\r${TICK} ${BGRN}Brew Installed ${RESET}${TICK}\n${DEF}"
    printf "\r${YELLOW} GLFW Installing ${RESET}\n${DEF}"
    brew install glfw
    printf "\r${TICK} ${BGRN}GLFW Installed ${RESET}${TICK}\n${DEF}"

}

printf "\r${YELLOW} Checking for Homebrew ${RESET}\n${DEF}"
if ! command -v brew &> /dev/null
then
    printf "\r${YELLOW} Homebrew Not Found ${RESET}\n${DEF}"
    printf "\r${YELLOW} Installing Homebrew ${RESET}\n${DEF}"
    brew_install
else
    printf "\r${TICK} ${BGRN}Homebrew Found ${RESET}${TICK}\n${DEF}"
    sleep 1
fi

rm -rf include
rm -rf lib
SYSTEM=$(uname)
if [ "$SYSTEM" == "Linux" ]; then
    cp -R /home/linuxbrew/.linuxbrew/Cellar/glfw/3.3.8/include/GLFW .
    cp -R /home/linuxbrew/.linuxbrew/Cellar/glfw/3.3.8/lib .
elif [ "$SYSTEM" == "Darwin" ]; then
    cp -R /Users/$USER/goinfre/.brew/Cellar/glfw/3.3.9/include/GLFW .
    cp -R /Users/$USER/goinfre/.brew/Cellar/glfw/3.3.9/lib .
fi
printf "\r${GRN} SETUP COMPLETE ${RESET}\n"