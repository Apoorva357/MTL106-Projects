#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>


using namespace std;


int main()
{



vector<int> arr(1000000);
// bool is_exist[200000];

// for(int i = 0;i<200001;i++){
//     arr[i] = 0;
//     // is_exist[i] = false;
// }

int size = 0;

vector<int> first_input;
vector<int> second_input;

// int inputsize;
// cin>>inputsize;

while(!cin.eof()){

    int a,b;
    cin>>a>>b;

    arr[a]++;

    first_input.push_back(a);
    second_input.push_back(b);

    size = max(size,a);
    size = max(size,b);

    // if(!is_exist[a]){
    //     is_exist[a] = true;
    //     size++;
    // }

    // if(!is_exist[b]){
    //     is_exist[b] = true;
    //     size++;
    // }

}

size += 1;
double fl_size = double(size);

// for(int i = 0;i<42;i++){
//     cout<<first_input[i]<<" "<<second_input[i]<<endl;
// }

// int mapping[size];
// int ind = 0;


// for(int i = 0;i<200000;i++){
//     if(is_exist[i]){
//         mapping[ind] = i;
//         ind++;
//     }
// }

vector<vector<double>> H(size); // Compressed H, only non zero entries are stored.

for(int i = 0;i<size;i++){
    H[i] = {};
}


// float one[size][size];
float A = 1/fl_size; // Compressed A, only the value 1/n is needed.
// cout<<A<<endl;
// for(int i = 0;i<size;i++){
//     for(int j = 0;j<size;j++){
//         H[i][j] = 0;
//         // one[i][j] = 1;
//     }
// }

int input_size = first_input.size();

vector<bool> is_dangling(size);

for(int i = 0;i<size;i++){
    is_dangling[i] = true;
}

vector<vector<int>> non_zero_elements(size); 

for(int i = 0;i<size;i++){
    non_zero_elements[i] = {};
}

for(int i = 0;i<input_size;i++){
    is_dangling[first_input[i]] = false;

    double weight = double(arr[first_input[i]]);
    H[second_input[i]].push_back(1/(weight));

    // cout<<first_input[i]<<" ";
    // cout<<1/weight<<endl;

    non_zero_elements[second_input[i]].push_back(first_input[i]);
}

vector<int> dangling_nodes;

for(int i = 0;i<size;i++){
    if(is_dangling[i]){
        dangling_nodes.push_back(i);      
    }

}

int ds = dangling_nodes.size();

double a = 0.85;

vector<double> I(size);

for(int i = 0;i<size;i++){
    I[i] = 1/fl_size;
    // cout<<I[i][1]<<endl;
}

int iterations = 1000;

 
vector<double> result_with_H(size);

while(iterations--){

    double result_with_1 = 0;
    for(int i = 0;i<size;i++){
        result_with_1 += I[i];
    }

    result_with_1 = result_with_1*(1-a);
    result_with_1 = result_with_1 / fl_size;   

    double result_with_A = 0;
    for(int j = 0;j<ds;j++){
        result_with_A = result_with_A + A * I[dangling_nodes[j]];
    }
    result_with_A = result_with_A*a;

    // cout<<result_with_A<<endl;

    
    for(int i = 0;i<size;i++){
        double temp = 0;
        int temp_size = non_zero_elements[i].size();

        for(int j = 0;j<temp_size;j++){
            temp = temp + H[i][j] * I[non_zero_elements[i][j]];
        }

        temp *= a;
        result_with_H[i] = temp;
    }

    double temp = 0;

    for(int i = 0;i<size;i++){
        double diff = (I[i] - result_with_H[i] - result_with_A - result_with_1)/I[i];
        temp = max(temp, -1*diff);
        temp = max(temp,diff); 
        I[i] = result_with_H[i] + result_with_A + result_with_1; 
        // cout<<I[1][1]<<endl;
    }

    if(temp <= 1e-5){
        break;
    }
        

}


double s = 0;
for(int i = 0;i<size;i++){
    cout<<i<<" = "<<setprecision(13)<<I[i]<<endl;
    s += I[i];
}

cout<<"s"<<" = "<<setprecision(7)<<s<<endl;

return 0;
}