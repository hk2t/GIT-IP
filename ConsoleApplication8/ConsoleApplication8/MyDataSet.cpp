#include "MyDataSet.h"
#include "cv.h"
using namespace cv;
using namespace std;

MyDataSet::MyDataSet(int rows, int cols){
    this->rows = rows;
    this->cols = cols;
}

void MyDataSet::Feed(Mat dataset){
    for (int j=0; j<dataset.rows; j++) {
        for (int i=0; i<dataset.cols; i++) {
            float color = dataset.at<float>(Point(i, j));
            if (color != -1) {this->size++;}
            MyData _myData(color);
            this->data.push_back(_myData);
        }
    }
    CalculateDist();
}

void MyDataSet::CalculateDist(){
    for (size_t i=0; i<this->data.size(); i++) {
        if (this->data[i].color == -1) {continue;}
        for (size_t j=0; j<this->data.size(); j++) {
            /*Vector<int> rcOther = ConvertToRowCol((int)j, this->cols);
            int _row = rcOther[0];
            int _col = rcOther[1];*/
            
            if (this->data[j].color == -1) {continue;}
            if (j != i) {// 2 diem k trung nhau
                int d = abs(this->data[i].color - this->data[j].color);
                Cell _cell;
                _cell.index = j;
                _cell.data = d;
                this->data[i].dist.push_back(_cell);
            }
        }

        //cout<<"this->data[i].dist = "<<this->data[i].dist.size()<<endl;
        Bubble_sort(this->data[i].dist);
        CalculateDist3(i);
    }
    CalculateLRD();
    CalculateLOF();
}

void MyDataSet::CalculateDist3(int index){
    if (this->data[index].dist.size() == 0) {return;}
    this->data[index].dist3.push_back(this->data[index].dist[0]);
    int num = 0;
    for (size_t i=1; i<this->data[index].dist.size(); i++) {
        int endIndex = this->data[index].dist3.size()-1;
        if (num < 3) {
            if (this->data[index].dist3[endIndex].data != this->data[index].dist[i].data) {
                num++;
                if (num == 3) {
                    break;
                }
            }
            this->data[index].dist3.push_back(this->data[index].dist[i]);
        }
    }
    // DEBUG
    /*
    for (size_t x=0; x<this->data[index].dist3.size(); x++) {
        int v = (int)(this->data[index].dist3[x].data);
        cout<<v<<", ";
    }
    cout<<endl;
    //*/
}

void MyDataSet::CalculateLRD(){
    for (size_t i=0; i<this->data.size(); i++) {
        if (this->data[i].color == -1) {continue;}
        float total = 0;
        for (size_t j=0; j<this->data[i].dist3.size(); j++) {
            int _data = this->data[i].dist3[j].data;
            int _index = this->data[i].dist3[j].index;
            if (this->data[_index].dist3[this->data[_index].dist3.size()-1].data > _data) {
                _data = this->data[_index].dist3[this->data[_index].dist3.size()-1].data;
            }
            total += _data;
        }
        if (total == 0) {
            this->data[i].LFD = 999;//++++
        }
        else {
            this->data[i].LFD = this->data[i].dist3.size()/total;
        }
    }
}

void MyDataSet::CalculateLOF(){
    for (size_t i=0; i<this->data.size(); i++) {
        if (this->data[i].color == -1) {continue;}
        float total = 0;    
        for (size_t j=0; j<this->data[i].dist3.size(); j++) {
            int neighbor = this->data[i].dist3[j].index;
            total += this->data[neighbor].LFD;
        }
        total /= this->data[i].LFD;
        total /= this->data[i].dist3.size();
        this->data[i].LOF = total;
    }
}

void MyDataSet::ShowPointData(int row, int col){
    int index = ConvertToIndex(row, col);

    //cout<<"dataset-(row"<<row<<",col"<<col<<")index = "<<index<<", data = "<<this->data[index].data<<endl;
    //cout<<"dist:";
    for (size_t i=0; i<this->data[index].dist.size(); i++) {
        cout<<data[index].dist[i].data<<"("<<data[index].dist[i].index<<")/";
    }

    //cout<<endl<<"dist3:";
    //for (size_t i=0; i<this->data[index].dist3.size(); i++) {
    //    cout<<this->data[index].dist3[i].data<<"("<<this->data[index].dist3[i].index<<")+";
    //}
    //cout<<endl<<endl;
}

void MyDataSet::ShowLRD(){
    cout<<endl<<"LRD:"<<endl;
    for (size_t i=0; i<this->data.size(); i++) {
        float lfd = this->data[i].LFD;
        if (lfd < 10) {
            printf("0%3.5f - ", lfd);
        }
        else {
            printf("%3.5f - ", lfd);
        }
        printf("%3.5f - ", this->data[i].LFD);
        if ((i+1)%this->rows == 0) {
            //cout<<endl;
        }
    }
}

void MyDataSet::ShowLOF(){
    cout<<endl<<"LOF:"<<this->data.size()<<endl;
    for (size_t i=0; i<this->data.size(); i++) {
        float lof = this->data[i].LOF;
        if (lof < 10) {
            printf("0%3.5f - ", this->data[i].LOF);
        }
        else {
            printf("%3.5f - ", this->data[i].LOF);
        }
        if ((i+1)%this->rows == 0) {
            //cout<<endl;
        }
    }
}

void MyDataSet::Bubble_sort(Vector<Cell> v) {
    for (size_t i = 0; i<v.size() - 1; i++) {
        for (size_t j = 0; j<v.size() - 1 - i; j++) {
            if (v[j].data > v[j + 1].data) {
                Cell temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

int MyDataSet::ConvertToIndex(int row, int col){
    return row*this->cols + col;
}

Vector<int> MyDataSet::ConvertToRowCol(int index, int cols){
    Vector<int> v;
    int row = index/cols;
    int col = index-row*cols;
    v.push_back(row);
    v.push_back(col);
    return v;
}