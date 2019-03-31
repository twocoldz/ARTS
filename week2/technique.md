#protobuf enum 校验

之前自己定义enum的时候，会定义一个xxx_MIN 和 xxx_MAX ，然后自己写一个bool Invalid（enum Type）的函数来判断这个值是否是合法的枚举。

后来组长review代码时才提醒，原来proto会为枚举生成一个Invalid的函数。

    enum DiscoveryActionType {                                                                                                  
    DISCOVERY_ACTION_TYPE_MIN = 0,                                                                                            
    DISCOVERY_ACTION_TYPE_PUBLISH = 1,                                                                                        
    DISCOVERY_ACTION_TYPE_LOVE = 2,                                                                                           
    DISCOVERY_ACTION_TYPE_REPLY = 3,                                                                                          
    DISCOVERY_ACTION_TYPE_MAX = 4                                                                                             
    };                                                                                                                          
    bool DiscoveryActionType_IsValid(int value);                                                                                
    const DiscoveryActionType DiscoveryActionType_MIN = DISCOVERY_ACTION_TYPE_MIN;                                              
    const DiscoveryActionType DiscoveryActionType_MAX = DISCOVERY_ACTION_TYPE_MAX;                                              
    const int DiscoveryActionType_ARRAYSIZE = DiscoveryActionType_MAX + 1;

    