#include <bits/stdc++.h>
using namespace std;
#define MAX_NUM 500
struct Edge
{
    int ver; // 节点编号
    int inde; // 节点入度
}edges[MAX_NUM];
int num = 0; // 记录文件中节点个数
vector<vector<int>> arr; // 记录读取的文件
bool visited[MAX_NUM]; // 记录是否访问过
int ver_map[MAX_NUM]; // 节点映射关系
vector<int> vers;
void init()
{
    for(int i = 0; i < MAX_NUM; i ++)
    {
        edges[i].ver = i;
        edges[i].inde = 0;
    }
}
void read_file(string file_path)
{
    std::ifstream file(file_path);
    string line;
    while(getline(file,line))
    {
        std::vector<int> row;
        stringstream ss(line);
        string tmp;
        while(std::getline(ss,tmp,' '))
        {
            int value = stoi(tmp);
            row.push_back(value);
        }
        arr.push_back(row);
    }
    
}
void count_Degree()
{
    // 根据读取的数据进行计数
    for (const auto& row : arr) 
    {
        //cout << row[0] << " " << row[1]<<endl;
        edges[row[1]].inde+=1;
        if(!visited[row[0]])
        {
            num += 1;
            vers.push_back(row[0]);
        }
        if(!visited[row[1]])
        {
            num += 1;
            vers.push_back(row[1]);
        } 
        visited[row[0]] = visited[row[1]] = 1;
    }
}
bool cmp(struct Edge &t1, struct Edge &t2)
{
    return t1.inde > t2.inde;
}
void ver_To_Next()
{
    for(int i = 0; i < num; i ++)
    {
        ver_map[edges[i].ver] = i;
    }
}
void write_file(string file_path)
{
    // 按照映射关系，输出重新排列之后的值
    std::ofstream file_out("output.txt");
    if(file_out.is_open())
    {
        std::ifstream file_read(file_path);
        string line;
        while(getline(file_read,line))
        {
            std::vector<int> row;
            stringstream ss(line);
            string tmp;
            while(std::getline(ss,tmp,' '))
            {
                int value = stoi(tmp);
                row.push_back(ver_map[value]);
            }
            //arr.push_back(row);
            file_out << row[0] << " " << row[1] << endl;
        }
        file_out.close();
    }
}
int main()
{
    string file_path = "./data/graph-csr.txt";
    read_file(file_path);
    init();
    count_Degree();
    sort(edges,edges+MAX_NUM,cmp);
    sort(vers.begin(),vers.end());
    ver_To_Next();
    write_file(file_path);
    return 0;
}