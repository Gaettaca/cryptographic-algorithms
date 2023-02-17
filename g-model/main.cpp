#include <iostream>
#include <time.h>
#include <random>
#include "g-model.h"

//void TestCBCEncryption(G &g) {
//    g.CBCEncryption(8, "lu-en.fb2", "CBC-lu-en-out.fb2");
//    g.CBCDecryption(8, "CBC-lu-en-out.fb2", "CBC-lu-en-dec.fb2");
//}
//
//void CBCAET(G &g) {
////    g.AET("lu-en.fb2");
////    g.AET("CBC-lu-en-out.fb2");
////    g.AET("CBC-lu-en-dec.fb2");
//}
//
//void MyCBCEncryptionTest(G &g) {
//    g.CBCEncryption(8, "my-test.txt", "my-test-out.txt");
//
////    g.AET("my-test.txt");
////    g.AET("my-test-out.txt");
//}

void ECB_AET_Test(G &g) {
    std::ofstream out("ECB-aet-test-res.txt");

    std::cout << "=====================[ ECB AET TEST ]======================\n";
    g.AET("my-test.txt", out);

    for (size_t i = 1; i <= 8; ++i) {
        std::cout << ">> clocks: " << i << "\n===============\n";
        g.ECBEncryption(i, "my-test.txt", "my-test-out.txt");
        g.AET("my-test-out.txt", out);
    }
    out.close();
}

void CBC_AET_Test(G &g) {
    std::ofstream out("CBC-aet-test-res.txt");

    std::cout << "=====================[ SMALL FILE CBC AET TEST ]======================\n";
    g.AET("my-test.txt", out);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(1, 255);

    int a = dist(rng);
    int b = dist(rng);

    for (size_t i = 1; i <= 8; ++i) {
        std::cout << ">> clocks: " << i << "\n===============\n";
        g.CBCEncryption(i, a, b, "my-test.txt", "my-test-out.txt");
        g.AET("my-test-out.txt", out);
    }
    out.close();
}

void OFB_AET_Test(G &g) {
    std::ofstream out("CBC-aet-test-res.txt");

    std::cout << "=====================[ SMALL FILE OFB AET TEST ]======================\n";
    g.AET("my-test.txt", out);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(1, 255);

    int a = dist(rng);
    int b = dist(rng);

    for (size_t i = 1; i <= 8; ++i) {
        std::cout << ">> clocks: " << i << "\n===============\n";
        g.OFBEncryption(i, a, b, "my-test.txt", "my-test-out.txt");
        g.AET("my-test-out.txt", out);
    }
    out.close();
}

void CFB_AET_Test(G &g) {
    std::ofstream out("CBC-aet-test-res.txt");

    std::cout << "=====================[ SMALL FILE CFB AET TEST ]======================\n";
    g.AET("my-test.txt", out);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(1, 255);

    int a = dist(rng);
    int b = dist(rng);

    for (size_t i = 1; i <= 8; ++i) {
        std::cout << ">> clocks: " << i << "\n===============\n";
        g.OFBEncryption(i, a, b, "my-test.txt", "my-test-out.txt");
        g.AET("my-test-out.txt", out);
    }
    out.close();
}

void MB_Test(G &g) {
    std::ofstream out("CBC-aet-test-res.txt");

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(1, 255);

    int a = dist(rng);
    int b = dist(rng);


//    std::cout << "=====================[ 1 MB CBC AET TEST ]======================\n";
//    g.AET("lu-en.fb2", out);
//    for (size_t i = 1; i <= 8; ++i) {
//        std::cout << "====[" << i << "]====\n";
//        g.CBCEncryption(i, a, b, "lu-en.fb2", "CBC-lu-out.fb2");
//        g.AET("CBC-lu-out.fb2", out);
//    }

    std::cout << "=====================[ 5 MB CBC AET TEST ]======================\n";
    a = dist(rng);
    b = dist(rng);
    g.AET("5MB.zip", out);
    for (size_t i = 1; i <= 8; ++i) {
        std::cout << "====[" << i << "]====\n";
        g.CBCEncryption(i, a, b, "5MB.zip", "5MB-out.zip");
        g.AET("5MB-out.zip", out);
    }

//    std::cout << "=====================[ 1 MB CFB AET TEST ]======================\n";
//    a = dist(rng);
//    b = dist(rng);
//    g.AET("lu-en.fb2", out);
//    for (size_t i = 1; i <= 8; ++i) {
//        std::cout << "====[" << i << "]====\n";
//        g.CFBEncryption(i, a, b, "lu-en.fb2", "CFB-lu-out.fb2");
//        g.AET("CFB-lu-out.fb2", out);
//    }
}

void OFB_Test(G &g) {
    std::ofstream out("CBC-aet-test-res.txt");


    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(1, 255);

    int a = dist(rng);
    int b = dist(rng);

    std::cout << "=====================[ SMALL FILE OFB TEST ]======================\n";
    g.AET("my-test.txt", out);
    g.OFBEncryption(8, a, b, "my-test.txt", "OFB-test-enc.txt");
    g.OFBDecryption(8, "OFB-test-enc.txt", "OFB-test-dec.txt");
    g.AET("OFB-test-enc.txt", out);
}

void CFB_Test(G &g) {
    std::ofstream out("CBC-aet-test-res.txt");


    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(1, 255);

    int a = dist(rng);
    int b = dist(rng);

    std::cout << "=====================[ SMALL FILE CFB TEST ]======================\n";
    g.AET("my-test.txt", out);
    g.CFBEncryption(8, a, b, "my-test.txt", "CFB-test-enc.txt");
    g.CFBDecryption(8, "CFB-test-enc.txt", "CFB-test-dec.txt");
    g.AET("CFB-test-enc.txt", out);
}

void Task3(G &g) {
    std::ofstream out("CBC-aet-test-res.txt");

    std::cout << "=====================[ ECB ENTROPY ]======================\n";
    g.Entropy("lu-en.fb2");
    for (size_t i = 1; i <= 8; ++i) {
        std::cout << "====[" << i << "]====\n";
        g.ECBEncryption(i, "lu-en.fb2", "ECB-entropy.fb2");
        g.Entropy("ECB-entropy.fb2");
    }
}

int main() {
    std::ofstream out("CBC-aet-test-res.txt");

//    G g(1976722673);
    G g(1152149393);

    MB_Test(g);
//    CBC_AET_Test(g);

//    OFB_Test(g);
//    OFB_AET_Test(g);
//    CFB_AET_Test(g);
//    CFB_Test(g);
//    Task3(g);
    return 0;
}
