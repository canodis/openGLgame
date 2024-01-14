TICK="✓"
BGRN="\033[1;32m"
GRN="\033[0;32m"
RESET="\033[0m"
RED="\033[0;31m"
YELLOW="\033[1;33m"
DEF="\033[0m"

dependencies()
{
    printf "\r${YELLOW} Checking for GLFW ${RESET}\n${DEF}"
    if [ -d "/Users/$USER/goinfre/.brew/Cellar/glfw" ]; then
        printf "\r${TICK} ${BGRN}GLFW Found ${RESET}${TICK}\n${DEF}"
        sleep 1
    else
        printf "\r${YELLOW} GLFW Not Found ${RESET}\n${DEF}"
        printf "\r${YELLOW} Installing GLFW ${RESET}\n${DEF}"
        brew install glfw
    fi
    printf "\r${YELLOW} Checking for Freetype ${RESET}\n${DEF}"
    if [ -d "/Users/$USER/goinfre/.brew/Cellar/freetype" ]; then
        printf "\r${TICK} ${BGRN}Freetype Found ${RESET}${TICK}\n${DEF}"
        sleep 1
    else
        printf "\r${YELLOW} Freetype Not Found ${RESET}\n${DEF}"
        printf "\r${YELLOW} Installing Freetype ${RESET}\n${DEF}"
        brew install freetype
        printf "\r${TICK} ${BGRN}Freetype Installed ${RESET}${TICK}\n${DEF}"
        printf "If vscode gives an error, you should add the location of the freetype to the 'includePath' in the c_cpp_properties.json file inside the .vscode. ${HOME}/goinfre/.brew/opt/freetype/include/freetype2 like this"
        sleep 1
    fi
}

brew_install()
{
    sleep 1
    git clone --depth=1 https://github.com/Homebrew/brew $HOME/goinfre/.brew
    echo "export PATH=$HOME/goinfre/.brew/bin:$PATH" >> $HOME/.zshrc
    source $HOME/.zshrc
    printf "\r${TICK} ${BGRN}Brew Installed ${RESET}${TICK}\n${DEF}"
   
    exit
}

printf "\r${YELLOW} Checking for Homebrew ${RESET}\n${DEF}"
if ! command -v brew &> /dev/null
then
    printf "\r${YELLOW} Homebrew Not Found ${RESET}\n${DEF}"
    printf "${RED}You need to restart this setup.sh after installing homebrew!!!!!!!!!!!${RESET}\n"
    sleep 1
    printf "\r${YELLOW} Installing Homebrew ${RESET}\n${DEF}"
    brew_install
    
    printf "\r${TICK} ${BGRN}Homebrew Installed ${RESET}${TICK}\n${DEF}"
    printf "${RED} Terminal terminating in 3 seconds ${RESET}\n"
    sleep 3
    TERMINAL_PID=$(ps -p $$ -o ppid=)
    kill -9 $TERMINAL_PID
else
    printf "\r${TICK} ${BGRN}Homebrew Found ${RESET}${TICK}\n${DEF}"
    sleep 1
fi

dependencies
rm -rf include
rm -rf lib
SYSTEM=$(uname)
if [ "$SYSTEM" == "Linux" ]; then
    cp -R /home/linuxbrew/.linuxbrew/Cellar/glfw/3.3.9/include/GLFW .
    cp -R /home/linuxbrew/.linuxbrew/Cellar/glfw/3.3.9/lib .
elif [ "$SYSTEM" == "Darwin" ]; then
    latest_glfw_path=$(ls -d /Users/$USER/goinfre/.brew/Cellar/glfw/* | tail -n 1)
    cp -R $latest_glfw_path/include/GLFW .
    cp -R $latest_glfw_path/lib .

fi
printf "\r${GRN} SETUP COMPLETE ${RESET}\n"