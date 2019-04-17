#pragma once
#include <QThread>
#include <vector>
#include <memory>
class Object;
class exportObjThread : public QThread {
	Q_OBJECT

public:
	exportObjThread();
	void setObjList(const std::vector<std::weak_ptr<Object>> &objList);
	void setFilePrefix(const QString& prefix);
signals:
	void exportingObjStatus(const QString&);
protected:
	void run();
private:
	QString filePrefix;
	std::vector<std::weak_ptr<Object>> objList;
};
