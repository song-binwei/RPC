#include "test.pb.h"
#include <iostream>
#include <string>

using namespace fixbug;

int main() {
    GetFriendListResponse rep;
    ResultCode *rc = rep.mutable_res();
    rc->set_errid(0);
    rc->set_errmsg("success");
    User *user1 = rep.add_friendlist();
    user1->set_name("bob");
    user1->set_age(23);
    user1->set_sex(User::man);

    User *user2 = rep.add_friendlist();
    user2->set_name("ALice");
    user2->set_age(18);
    user2->set_sex(User::woman);

    std::string repStr;

    if(rep.SerializeToString(&repStr)) {
        std::cout << "Serialize Success" << std::endl;
        std::cout << repStr << std::endl;
    }
    
    GetFriendListResponse res;
    if(res.ParseFromString(repStr)) {
        std::cout << "Parse : " << std::endl;
        ResultCode res_rc = res.res();
        std::cout << res_rc.errid() << std::endl;
        std::cout << res_rc.errmsg() << std::endl;
        for(int i = 0; i < res.friendlist_size(); i++) {
            const User resu = res.friendlist(i);
            std::cout << resu.name() << std::endl;
            std::cout << resu.age() << std::endl;
            std::cout << resu.sex() << std::endl;
        }
        
    }

    return 0;
}






// int main2() {

//     fixbug::GetFriendListResponse friendList;
//     fixbug::ResultCode *rc = friendList.mutable_res();
//     rc->set_errid(0);

//     fixbug::User *user1 = friendList.add_friendlist();
//     user1->set_name("zhang san");
//     user1->set_age(10);
//     user1->set_sex(fixbug::User::man);

//     fixbug::User *user2 = friendList.add_friendlist();
//     user2->set_name("zhao si");
//     user2->set_age(20);
//     user2->set_sex(fixbug::User::woman);

//     std::cout << friendList.friendlist_size() << std::endl;

//     std::string ret;
//     friendList.SerializeToString(&ret);
//     std::cout << "Serialize : " << std::endl;
//     std::cout << ret << std::endl;
    

//     fixbug::GetFriendListResponse req;
//     if(req.ParseFromString(ret)) {
//         std::cout << "Parse : " << std::endl;
//         fixbug::ResultCode reqrc = req.res();
//         std::cout << reqrc.errid() << std::endl;
//         std::cout << reqrc.errmsg() << std::endl;
//         fixbug::User& req_user = req.friendlist(1);
//         std::cout << req_user.age() << std::endl;
//         std::cout << req_user.name() << std::endl;
//     }



//     return 0;
// }

// int main1() {

//     fixbug::LoginRequest req;
//     req.set_name("zhangshan");
//     req.set_pwd("123456");
//     std::string strRet;
//     if(req.SerializeToString(&strRet)) {
//         std::cout << strRet << std::endl;
//     }

//     fixbug::LoginRequest reqRes;
//     if(reqRes.ParseFromString(strRet)) {
//         std::cout << reqRes.name() << std::endl;
//         std::cout << reqRes.pwd() << std::endl;
//     }

//     return 0;
// }