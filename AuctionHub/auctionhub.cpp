/*
    Author: Tran Truong Trung Hieu
    Latest Update: 25/11/2026
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;

struct Bid {
    string bidderId;
    double amount;       // bid price
    long long timestamp; // Unix ms
    int auctionId;
};

// ---------- Utilities ----------
void printBids(const vector<Bid>& v, size_t limit = 10) {
    for (size_t i = 0; i < min(v.size(), limit); ++i)
        cout << "[" << v[i].bidderId << "] $" << v[i].amount
        << " @ " << v[i].timestamp << "\n";
    if (v.size() > limit) cout << "... (" << v.size() << " total)\n";
}

bool loadBids(const string& path, vector<Bid>& out) {
    ifstream f(path);
    if (!f) return false;
    Bid b;
    while (f >> b.bidderId >> b.amount >> b.timestamp >> b.auctionId)
        out.push_back(b);
    return true;
}

// ---------- TODO: Implement these ----------
bool comparisons(const Bid& a, const Bid& b) {
    if (a.amount == b.amount) {
        return a.timestamp < b.timestamp;
    }
    return a.amount < b.amount;
}
void insertionSort(vector<Bid>& v)          // Task A
{
    for (int i = 1; i < v.size(); ++i) {
        Bid k = v[i];
        int j = i - 1;
        while (j >= 0 && comparisons(k, v[j])) {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = k;
    }
}
void selectionSort(vector<Bid>& v)          // Task B
{
    for (int i = 0; i < v.size(); ++i) {
        int max = i;
        for (int j = i + 1; j < v.size(); ++j) {
            if (v[j].amount > v[max].amount) {
                max = j;
            }
        }
        swap(v[i], v[max]);
    }
	cout << "Top 3 are:\n";
    for (int i = 0; i < min(v.size(), (size_t)3); ++i) {
        cout << v[i].bidderId << "\t";
    }
}
void interchangeSort(vector<Bid>& v)        // Task C
{
    int Count = 0;
    for (int i = 0; i < v.size(); ++i) {
        for (int j = i + 1; j < v.size(); ++j) {
            if (v[i].amount > v[j].amount) {
                swap(v[i], v[j]);
                Count++;
            }
        }
    }
    cout << "Total number of swaps: " << Count << "\n";
}
bool bubbleSortEarlyStop(vector<Bid>& v)    // Task D — returns true if stable (no swaps on a full pass)
{
    bool stop = true;
    for (int i = 0; i < v.size(); ++i) {
        bool swapped = false;
        for (int j = 0; j < v.size() - i - 1; ++j) {
            if (v[j].amount > v[j + 1].amount) {
                swap(v[j], v[j + 1]);
                swapped = true;
                if (i == 0) stop = false;
            }
        }
        if (!swapped) break;
    }
    if (stop) {
        cout << "STABLE\n";
        return true;
    }
    else {
        cout << "UNSTABLE\n";
        return false;
    }
}
int medianOfThree(vector<Bid>& v, int lo, int hi) {
	if (lo >= hi) return lo;
    int mid = (lo + hi) / 2;
    if(comparisons(v[mid],v[lo]))
		swap(v[mid], v[lo]);
	if(comparisons(v[hi], v[lo]))
		swap(v[hi], v[lo]);
    if(comparisons(v[hi], v[mid]))
		swap(v[hi], v[mid]);
    return mid;
}
int partition(vector<Bid>& v, int lo, int hi) {
	int index = medianOfThree(v, lo, hi);
	swap(v[index], v[hi]);
	Bid pivot = v[hi];
	int i = lo - 1;
	for (int j = lo; j < hi; j++) {
		if (comparisons(v[j], pivot)) {
			i++;
			swap(v[i], v[j]);
		}
	}
	swap(v[i + 1], v[hi]);
	return i + 1;
}
void quickSort(vector<Bid>& v, int lo, int hi) // Task E
{
	if (lo < hi) {
		int pi = partition(v, lo, hi);
		quickSort(v, lo, pi - 1); /* sort left part */
		quickSort(v, pi + 1, hi); /* sort right part */
	}
}

void quickSortWrapper(vector<Bid>& v) {
    if (v.empty()) return;
    auto start = chrono::high_resolution_clock::now();
    quickSort(v, 0, v.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    auto time_taken = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Runtime: " << time_taken << " miliseconds\n";
}
//Generate random datas (Use LLM to create this function)
void generateRandomBids() {
    ofstream file("D:/AuctionHub/test_data/large.txt");
    if (!file.is_open()) {
        cout << "Error opening file!\n";
        return;
    }
    mt19937 gen(random_device{}());
    uniform_real_distribution<double> amountDist(100, 1000000);
    uniform_int_distribution<long long> timestampDist(1, 1000000000);
    uniform_int_distribution<int> auctionDist(1, 100);
    for (int i = 0; i < 100000; i++) {
        string bidderId = "Bidder_" + to_string(i + 1);
        double amount = amountDist(gen);
        long long timestamp = timestampDist(gen);
        int auctionId = auctionDist(gen);
        file << bidderId << " "
            << amount << " "
            << timestamp << " "
            << auctionId << "\n";
    }
    file.close();
    cout << "Generated 100000 bids successfully!\n";
}

// ---------- Driver ----------
int main(int argc, char* argv[]) {
    vector<Bid> smallData;
	if (!loadBids("D:/AuctionHub/test_data/small.txt", smallData)) {
		cout << "Failed to load small.txt\n";
		return 1;
	}
    //Test task A
	cout << "Task A: Insertion Sort\n";
	vector<Bid> testA(smallData.begin(), smallData.begin()+4);
    insertionSort(testA);
    printBids(testA);
	cout << "\n==============================\n";
	//Test task B
	cout << "Task B: Selection Sort\n";
	vector<Bid> testB(smallData.begin(), smallData.begin()+4);
	selectionSort(testB);
	//Test task C
	cout << "\n==============================\n";
	cout << "Task C: Interchange Sort\n";
    vector<Bid> testC(smallData.begin() + 4, smallData.begin() + 8);
    interchangeSort(testC);
	//Test task D
	cout << "\n==============================\n";
	cout << "Task D: Bubble Sort Early Stop\n";
	cout << "Test 1: Sorted input\n";
	vector<Bid> testD1(smallData.begin() + 8, smallData.begin() + 12);
    bubbleSortEarlyStop(testD1);
    cout << "Test 2: Reversed input\n";
    vector<Bid> testD2(smallData.begin() + 12, smallData.end());
    bubbleSortEarlyStop(testD2);
    //Test task E
    cout << "\n==============================\n";
    cout << "Task E: Quick Sort\n";
    generateRandomBids();
    vector<Bid> bids;
    loadBids("D:/AuctionHub/test_data/large.txt", bids);
    quickSortWrapper(bids);
    cout << "After sorting:\n";
    printBids(bids, 5);
    return 0;
}
