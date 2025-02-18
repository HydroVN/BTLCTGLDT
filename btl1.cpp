#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;
const int MAX_STUDENTS = 200;  // Gioi han so luong sinh vien
struct Student {
    string id;
    string name;
    int birthYear;
    float averageScore;
};
// Ham hien thi danh sach sinh vien
void displayStudents(Student students[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "ID: " << students[i].id
             << ", Name: " << students[i].name
             << ", Birth Year: " << students[i].birthYear
             << ", Average Score: " << students[i].averageScore << endl;
    }
    cout << "-----------------------------------" << endl;
}
// Ham doc du lieu tu file
int readStudentsFromFile(const string& filename, Student students[]) {
    ifstream file(filename.c_str()); // Chuyển đổi std::string sang const char*
    // Kiem tra xem file co mo duoc khong
    if (!file) {
        cerr << "Khong the mo file: " << filename << endl;
        return 0;
    }
    string line;
    int count = 0;
    while (getline(file, line) && count < MAX_STUDENTS) {
        if (line.empty()) continue;  // Bo qua dong trong
        stringstream ss(line);
        getline(ss, students[count].id, ',');
        getline(ss, students[count].name, ',');
        ss >> students[count].birthYear;
        ss.ignore();
        ss >> students[count].averageScore;
        if (ss.fail()) {  // Kiem tra loi doc du lieu
            cerr << "Du lieu khong hop le tai dong " << count + 1 << ": " << line << endl;
            ss.clear(); // Xoa co loi va tiep tuc
            continue;
        }
        count++;
    }
    file.close();
    return count;
}
void selectionSort(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (students[j].name < students[minIdx].name) {
                minIdx = j;
            }
        }
        swap(students[i], students[minIdx]);
    }
}
void merge(Student students[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Student leftArr[n1], rightArr[n2];
    for (int i = 0; i < n1; i++) leftArr[i] = students[left + i];
    for (int i = 0; i < n2; i++) rightArr[i] = students[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i].name <= rightArr[j].name) {
            students[k] = leftArr[i];
            i++;
        } else {
            students[k] = rightArr[j];
            j++;
        }
        k++;
    }
    while (i < n1) students[k++] = leftArr[i++];
    while (j < n2) students[k++] = rightArr[j++];
}
void mergeSort(Student students[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(students, left, mid);
        mergeSort(students, mid + 1, right);
        merge(students, left, mid, right);
    }
}
int partition(Student students[], int low, int high) {
    string pivot = students[high].name;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (students[j].name < pivot) {
            i++;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]);
    return i + 1;
}
void quickSort(Student students[], int low, int high) {
    if (low < high) {
        int pi = partition(students, low, high);
        quickSort(students, low, pi - 1);
        quickSort(students, pi + 1, high);
    }
}
// Ham tim kiem sinh vien theo ID
void searchStudentById(Student students[], int n, const string& id) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (students[i].id == id) {
            cout << "Student found:" << endl;
            cout << "ID: " << students[i].id
                 << ", Name: " << students[i].name
                 << ", Birth Year: " << students[i].birthYear
                 << ", Average Score: " << students[i].averageScore << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Student with ID " << id << " not found!" << endl;
    }
}
// Ham tim kiem sinh vien theo ten (co the trung khop mot phan)
void searchStudentByName(Student students[], int n, const string& name) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        // Kiem tra neu ten nhap vao la mot phan cua ten sinh vien
        if (students[i].name.find(name) != string::npos) {
            cout << "Student found:" << endl;
            cout << "ID: " << students[i].id
                 << ", Name: " << students[i].name
                 << ", Birth Year: " << students[i].birthYear
                 << ", Average Score: " << students[i].averageScore << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No student found with name containing: " << name << endl;
    }
}
int main() {
    Student students[MAX_STUDENTS];
    int n = readStudentsFromFile("students.txt", students);
    if (n == 0) {
        cout << "Khong co sinh vien nao hoac loi file!" << endl;
        return 1;
    }
    int choice;
    string input;
    do {
        cout << "\nMenu:\n";
        cout << "1. Hien thi danh sach sinh vien\n";
        cout << "2. Sap xep danh sach sinh vien bang Selection Sort\n";
        cout << "3. Sap xep danh sach sinh vien bang Merge Sort\n";
        cout << "4. Sap xep danh sach sinh vien bang Quick Sort\n";
        cout << "5. Tim kiem sinh vien theo ID\n";
        cout << "6. Tim kiem sinh vien theo ten\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Danh sach sinh vien ban dau:" << endl;
                displayStudents(students, n);
                break;
            case 2:
                {
                    Student selectionSorted[MAX_STUDENTS];
                    copy(students, students + n, selectionSorted);
                    selectionSort(selectionSorted, n);
                    cout << "Sau khi sap xep chon:" << endl;
                    displayStudents(selectionSorted, n);
                }
                break;
            case 3:
                {
                    Student mergeSorted[MAX_STUDENTS];
                    copy(students, students + n, mergeSorted);
                    mergeSort(mergeSorted, 0, n - 1);
                    cout << "Sau khi sap xep tron:" << endl;
                    displayStudents(mergeSorted, n);
                }
                break;
            case 4:
                {
                    Student quickSorted[MAX_STUDENTS];
                    copy(students, students + n, quickSorted);
                    quickSort(quickSorted, 0, n - 1);
                    cout << "Sau khi sap xep nhanh:" << endl;
                    displayStudents(quickSorted, n);
                }
                break;
            case 5:
                cout << "Nhap ID sinh vien can tim: ";
                cin >> input;
                searchStudentById(students, n, input);
                break;
            case 6:
                cout << "Nhap ten sinh vien can tim: ";
                cin.ignore(); // Bo qua ky tu newline truoc do
                getline(cin, input); // Doc ca dong ten
                searchStudentByName(students, n, input);
                break;
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }
    } while (choice != 0);
    return 0;
}