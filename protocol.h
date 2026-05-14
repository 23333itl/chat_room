#pragma once
#pragma pack(push, 1)
// // 文件传输类型
// #define FILE_UPLOAD_REQ 10
// #define FILE_UPLOAD_ACK 11
// #define FILE_DATA       12
// #define FILE_PROGRESS   13
// #define FILE_COMPLETE   14
// #define FILE_ERROR      15

// 控制消息：chunkSize == 0，fileName 放状态字符串
// 数据消息：chunkSize > 0，fileName 放真实文件名
struct FileChunk {
    int fileId;          // 文件ID
    int chunkIndex;      // 块序号（控制消息时无意义）
    int chunkSize;       // 数据大小（0=控制消息，>0=数据）
    int totalChunks;     // 总块数
    long long fileSize;  // 文件总大小
    char fileName[128];  // 控制消息时放状态，数据消息时放文件名
    char data[0];        // 柔性数组，实际数据
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

//文件传输状态枚举，避免字符串比较
enum FileStatus {
    FILE_DATA = 0,      // 普通数据块
    FILE_PUSH = 1,      // 服务器推送文件头
    FILE_ACK = 2,       // 确认/进度回复
    FILE_COMPLETE = 3,  // 传输完成
    FILE_ERROR = 4      // 错误
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
