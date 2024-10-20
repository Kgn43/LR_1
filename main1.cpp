//#include <iostream>
//#include <future>
//#include <vector>
//#include <mutex>
//
//using namespace std;
//
//
//struct CTF{
//    int money = 0;
//    mutex mmm;
//    bool Pay(int mon){
//        lock_guard<mutex> ggg(mmm);
//        if (mon <= money){
//            money -= mon;
//            return true;
//        }
//        return false;
//    }
//};
//
//
//int MinusMoney(CTF& ctf){
//    int result = 0;
//    for (size_t i = 0; i < 1'000'000; i++){
//        if (ctf.Pay(100)) {
//            result += 100;
//        }
//    }
//    return result;
//}
//
//
//int main()
//{
//    CTF team{1'000'000};
//    auto x = async(MinusMoney, ref(team));
//    auto xx = async(MinusMoney, ref(team));
//    auto xxx = async(MinusMoney, ref(team));
//    auto xxxx = async(MinusMoney, ref(team));
//    auto xxxxx = async(MinusMoney, ref(team));
//    cout << (x.get() + xx.get() + xxx.get() + xxxx.get() + xxxxx.get()) << endl;
//    cout << team.money << endl;
//    return 0;
//}

#include <iostream>
#include <thread>
#include <mutex>
#include <future>

using namespace std;


int main(){
    cout << this_thread::get_id() << endl;
    thread t([](){
        cout << this_thread::get_id() << endl;
    });
    t.join();
   // t.detach();
    return 0;
}