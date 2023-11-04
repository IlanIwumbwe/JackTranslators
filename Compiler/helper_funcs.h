#ifndef HELPER_FUNCS_H
#define HELPER_FUNCS_H

// common imports
#include <string>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <regex>
#include <iostream>
#include <fstream>

// namespace for filesystem
namespace fs = std::filesystem;

// helper struct
struct XML_TAGS{
    //std::string keyword = 
    //std::string symbol = 
    //std::string int_const = 
    //std::string str_const = 
    //std::string identifier = 
    static std::string GetXmlTag(std::string tkn_type){
        if (tkn_type == "KEYWORD"){
            return "<keyword>_</keyword>";
        } else if (tkn_type == "SYMBOL"){
            return "<symbol>_</symbol>";
        } else if (tkn_type == "INT_CONST"){
            return "<integerConstant>_</integerConstant>";
        } else if (tkn_type == "STRING_CONST"){
            return "<stringConstant>_</stringConstant>";
        } else {
            return "<identifier>_</identifier>";
        }
    }
};

// helper functions

/// Returns a vector of paths
std::vector<std::string> GetFilesToParse(std::string& path, std::string input_extension){
    std::vector<std::string> paths;

    if (!fs::is_directory(path)){
        paths.push_back(path);
        return paths;
    } else{
        std::string main_path = "";

        // enforce compilation order so that all classes are defined
        for (const auto& entry : fs::directory_iterator(path))
        {   
            if (entry.path().filename() == "Main" + input_extension){
                main_path = entry.path().string();
            } else if (entry.path().extension() == input_extension){
                paths.push_back(entry.path().string());
            }
        }

        if (main_path == ""){
            std::cout << "Entry point should be named 'Main'" << std::endl;
        } else {
            paths.push_back(main_path);
        }   
    }

    return paths;
}

std::string GetOutputPath(std::string& input_path, std::string output_extension, std::string compiler_flag){
    auto path = fs::path(input_path);

    if (fs::is_directory(path)){
        return path / (path.filename().string() + output_extension);
        
    } else {
        if (compiler_flag != ""){
            output_extension = (compiler_flag == "T") ? "T.xml" : ".xml";
        }

        std::regex pattern(path.filename().extension().string());
        return std::regex_replace(path.string(), pattern, output_extension);
    }
}

std::vector<std::string> splitString(const std::string& input, const std::string& delimiter){
    std::vector<std::string> result;
    std::regex regexDelimiter(delimiter);
    std::sregex_token_iterator iterator(input.begin(), input.end(), regexDelimiter, -1);

    // Use sregex_token_iterator to split the string and add tokens to the result vector
    while (iterator != std::sregex_token_iterator()) {
        result.push_back(*iterator);
        ++iterator;
    }

    return result;
}

std::string removeWhiteSpace(std::string str){
    std::regex pattern(R"(^\s+|\s+$)");

    return std::regex_replace(str, pattern, "");
}

std::string GetTokenXML(std::string tkn, std::string tkn_type){
    std::string xml = XML_TAGS::GetXmlTag(tkn_type);
    std::regex pattern("_");
    
    if (tkn == "<"){
        return std::regex_replace(xml, pattern, " &lt; ");
    } else if (tkn == ">"){
        return std::regex_replace(xml, pattern, " &gt; ");
    } else if (tkn == "\""){
        return std::regex_replace(xml, pattern, " &quot; ");
    } else if (tkn == "&"){
        return std::regex_replace(xml, pattern, " &amp; ");
    } else {
        std::regex str_const_pattern(R"("[^\n\"]+")");

        if (std::regex_match(tkn, str_const_pattern)){
            tkn.erase(std::remove(tkn.begin(), tkn.end(), '\"'), tkn.end());
        }
        return std::regex_replace(xml, pattern, " "  + tkn + " ");
    }
}


#endif