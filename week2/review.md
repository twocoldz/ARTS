[What happens when you type 'google.com' into a browser and press Enter?](https://dev.to/antonfrattaroli/what-happens-when-you-type-googlecom-into-a-browser-and-press-enter-39g8)

1. 浏览器通过判断输入是否为网页链接，决定下一步的操作
2. 对于网页链接，如果没有http[s]开头的情况，默认加http；没有指定端口的情况下默认访问80端口
3. 随后会发起DNS请求，进行域名解析，得到一组IP地址
4. 随后发起HTTP请求，涉及到网络协议栈包括应用层（http),传输层（TCP/UDP），网络层（IP），数据链路层（ARP、RARP）等
5. google会返回要求是用https进行通信，并告知支持的TLS版本
6. google可能还会做一些安全策略，判断是否是一个恶意请求
7. 对于google主页的请求，google会通过边缘计算节点直接返回主页相对固定的内容
8. 浏览器会对回报进行解压，因为为了节省带宽资源，是会压缩的
9. 目前的google大部分协议使用的会是HTTP2.0， 可能还会有QUIC（TLS on UDP）
10. 后续可能会拉去一些用户相关的信息等

更多：
TLS证书下发问题
cname使用301重定向， http到https使用307
