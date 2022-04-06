#ifndef MYSERVER_H
#define MYSERVER_H

class MyServer : public QtcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // MYSERVER_H
