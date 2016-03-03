#include "gtest/gtest.h"
#include "inc.h"
#include "stl_headers.h"
#include <functional>
#include <algorithm>
#include <array>
#include <iterator>
#include <regex>
#include <fstream>

NS_BEGIN(elloop);

using namespace std;
using namespace std::placeholders;




//-----------------------  Advance  ----------------------
BEGIN_TEST(RegexTest, Unicode, @);

std::string s("this subject has a submarine as a subsequence");
//std::regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub"
std::regex e("\\s*[^\u4e00-\u9fa5]+\\s*");

std::regex_iterator<std::string::iterator> rit(s.begin(), s.end(), e);
std::regex_iterator<std::string::iterator> rend;

while (rit != rend)
{
    std::cout << rit->str() << std::endl;
    ++rit;
}

//char32_t utf32[] = U"hello = \u4F60\u597D\u554A";


END_TEST;




void read_from_file(const string& file_name, vector<string>& output)
{
    if (file_name.empty())
    {
        cout << "bad input file name!" << endl;
        return;
    }

    ifstream in_stream(file_name.c_str(), ifstream::in);
    if (in_stream.is_open())
    {
        output.clear();
        string line;
        while (getline(in_stream, line))
        {
            output.push_back(line);
        }
        in_stream.close();
    }
}

void convert_highlight(vector<string>& content, const string& cmd)
{
    string pattern_begin;
    string pattern_end;
    regex regex_begin;
    regex regex_end;
    string replace_begin;
    string replace_end;

    if ((cmd) == "--to-dot")
    {
        // match {% highlight <lan> %} and {% endhighlight %}, then replace with ```<lan> and ```.
        pattern_begin = "\\{[\\s\\t]*%[\\s\\t]*\\bhighlight[\\s\\t]*(\\S+)[\\s\\t]*%[\\s\\t]*\\}[\\s\\t]*";
        regex_begin = pattern_begin;
        pattern_end = "\\{[\\s\\t]*%[\\s\\t]*endhighlight[\\s\\t]*%[\\s\\t]*\\}";
        regex_end = pattern_end;
        replace_begin = "```$1";
        replace_end = "```";
    }
    else
    {
        // match ```<lan> and ```, then replace with {% highlight <lan> %} and {% endhighlight %}.
        pattern_begin = "```(\\S+)[\\s\\t]*";
        regex_begin = pattern_begin;
        pattern_end = "```[\\s\\t]*";
        regex_end = pattern_end;
        replace_begin = "{% highlight $1 %}";
        replace_end = "{% endhighlight %}";
    }

    // check every line, try to match begin and end.
    vector<string> backup;
    backup.swap(content);

    size_t match_count(0);
    for (auto & line : backup)
    {
        //line = "```c++            ";
        smatch sm;
        // try to match begin.
        regex_match(line, sm, regex_begin);
        if (sm.size() == 2)
        {
            cout << "replace: " << line << endl;
            line = regex_replace(line, regex_begin, replace_begin);
            ++match_count;
            continue;
        }

        regex_match(line, sm, regex_end);
        if (sm.size() == 1)
        {
            cout << "replace: " << line << endl;
            line = regex_replace(line, regex_end
                , replace_end);
            ++match_count;
        }
    }

    // override contents.
    content.swap(backup);
    cout << "total replace: " << match_count << endl;
}

void write_to_file(const string& file_name, const vector<string>& content)
{
    if (file_name.empty())
    {
        return;
    }

    ofstream out(file_name.c_str(), fstream::out);
    if (out.is_open())
    {
        for (const auto& line : content)
        {
            out << line << endl;
        }
        out.close();
    }
}

void printUsage()
{
    string help =
        "usage:                           \n"
        "                                 \n"
        " --to-rouge <file-name> : convert style from ```<language> to {% highlight <language> %} style \n"
        " --to-dot   <file-name> : convert from {% highlight <language> %} to ```<language>\n";
    cout << help;
}


RUN_GTEST(RegexTest, convert, @@);

string srcfile_name("2015-12-15-learning-using-stl-12-std-bind.md");
string flag("--to-rouge");
string dstfile_name = srcfile_name.substr(0, srcfile_name.rfind('.')) + "-for-csdn.md";

cout << "src: " << srcfile_name << endl;
cout << "dst: " << dstfile_name << endl;


vector<string> content;
read_from_file(srcfile_name, content);
convert_highlight(content, flag);
write_to_file(dstfile_name, content);

END_TEST;   



NS_END(elloop);