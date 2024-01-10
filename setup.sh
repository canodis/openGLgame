brew_install()
{
    git clone --depth=1 https://github.com/Homebrew/brew $HOME/goinfre/.brew
    echo "export PATH=$HOME/goinfre/.brew/bin:$PATH" >> $HOME/.zshrc
    source $HOME/.zshrc
    printf “\r${TICK} ${BGRN}Brew Installed ${TICK}\n${DEF}”
    brew install glfw
}
# brew_install
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
make re