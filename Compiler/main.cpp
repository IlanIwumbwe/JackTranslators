#include "Lexer.h"
#include "Compiler.h"
#include "Tokeniser.h"
#include "VMtranslator.h"
#include <unistd.h>

void vmToASM(std::string& path, VMtranslator& vmt){
    auto vmfiles = GetFilesToParse(path, ".vm");
    auto output_path = GetOutputPath(path, ".asm", "");
    std::ofstream outfile(output_path);

    vmt.Translate(vmfiles, outfile);
    std::cout << "Done writing assembly to: " << output_path << std::endl;
}

void compileCode(std::string path, const char* initialform, const char* finalform, bool saveTokens){
    Compiler cp;
    CompilerXML cpXML;
    Lexer lexer;
    VMtranslator vmt;

    std::vector<std::string> paths;
    std::string output_path;

    if (strcmp(initialform,"jack") == 0){
        paths = GetFilesToParse(path, ".jack");

        for (std::string path : paths){
            output_path  = "";
            // for each file, set it as the file to be tokenised, tokenise and save them in an xml doc
            lexer.SetFilePath(path);
            lexer.Lex();
            
            // this compiler gives .vm output
            lexer.InitialiseCurrToken(); // set current token to top of token buffer
            output_path = GetOutputPath(path, ".vm", "");
            cp.Compile(output_path, lexer);

            // if user wants tokens saved
            if(saveTokens){
                lexer.SaveTokens(path);  // save program tokens   

                // this compiler gives XML output
                lexer.InitialiseCurrToken(); // set current token to top of token buffer
                output_path = GetOutputPath(path, ".xml", "C");
                cpXML.Compile(output_path, lexer);
            }

        }
        
        if(strcmp(finalform, "vm") == 0){
            std::cout << "Jack code compiled into VM code" << std::endl;

        } else if (strcmp(finalform, "asm") == 0 ) {
            vmToASM(path, vmt);

        } else {
            std::cout << "Wrong final form" << std::endl;
        }


    } else if (strcmp(initialform, "vm") == 0){
        if (strcmp(finalform,"asm") == 0){
            vmToASM(path, vmt);
            
        } else {
            std::cout << "Wrong final form " << std::endl;
        }

    } else {
        std::cout << "Wrong initial form " << std::endl;
    }
}

int main(int argc, char* argv[]){
    std::string path = "";
    const char* initialform = nullptr;
    const char* finalform = nullptr;
    bool saveTokens = false;

    int opt;
    while ((opt = getopt(argc, argv, "p:i:f:t")) != -1) {
        switch (opt) {
            case 'p':
                path = optarg;
                break;
            case 'i':
                initialform = optarg;
                break;
            case 'f':
                finalform = optarg;
                break;
            case 't':
                saveTokens = true;
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " -p <path> -i <initial> -f <final> -t" << std::endl;
                return 1;
        }
    }

    if (path == "" || initialform == nullptr || finalform == nullptr) {
        std::cerr << "Usage: " << argv[0] << " -p <path> -i <initial> -f <final> -t" << std::endl;
        std::cerr << "Missing required arguments." << std::endl;
        return 1;
    }

    std::cout << "Path: " << path << std::endl;
    std::cout << "Initial form: " << initialform << std::endl;
    std::cout << "Final form: " << finalform << std::endl;
    std::cout << "Save tokens flag: " << (saveTokens ? "true" : "false") << std::endl;

    compileCode(path, initialform, finalform, saveTokens);


    return 0;
}