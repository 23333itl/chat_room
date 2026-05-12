#pragma once
#pragma pack(push, 1)
// // 文件传输类型
// #define FILE_UPLOAD_REQ 10
// #define FILE_UPLOAD_ACK 11
// #define FILE_DATA       12
// #define FILE_PROGRESS   13
// #define FILE_COMPLETE   14
// #define FILE_ERROR      15

struct FileChunk {
    int fileId;
    int chunkIndex;
    int chunkSize;
    int totalChunks;
    long long fileSize;
    char fileName[128];
    char data[0];  // 文件内容
};

// 消息结构体
struct ChatMsg {
    int totalLen;    // 1.总长 = sizeof(ChatMsg) + 内容长度
    int type;        // 2.类型 0=默认测试消息 1=登录 2=聊天 3=退出 4=心跳包 5=发送密码 6=文件传输 7=文件名 8=文件请求 9=请求文件列表
    //char name[20];   // 3.发送者用户名
    char content[0]; // 3.标记内容地址
};

// 文件通知结构体（通知其他用户有新文件）
struct FileNotify {
    int fileId=0;              // 文件ID
    long long fileSize;      // 文件大小
    char fileName[128];      // 文件名
};
// enum class MsgType : int
// {
//
//     Login       = 1,    // 登录
//     Chat        = 2,    // 普通聊天
//     File        = 3,    // 文件传输
//     HeartBeat   = 4,    // 心跳包
//     Logout      = 5,    // 退出登录
//     UserList    = 6,    // 在线用户列表
//     PrivateChat = 7     // 私聊
//
// };

#pragma pack(pop)

#define CHUNK_SIZE (64 * 1024)  // 64KB
