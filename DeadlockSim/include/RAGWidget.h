#ifndef RAGWIDGET_H
#define RAGWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QString>
#include <QResizeEvent>

struct RAGNode {
    QString label;   // e.g. "P0", "R1"
    bool isProcess;  // true = circle, false = square
    QPointF pos;
};

struct RAGEdge {
    int from;        // index into nodes
    int to;
    bool isRequest;  // true = P→R (request), false = R→P (assignment)
};

class RAGWidget : public QWidget {
    Q_OBJECT
public:
    explicit RAGWidget(QWidget* parent = nullptr);

    void setGraph(int numProcesses, int numResources,
                  const QVector<QVector<int>>& allocation,   // R→P
                  const QVector<QVector<int>>& request,      // P→R
                  const QVector<int>& deadlocked);

    void clear();

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;  // FIX: re-layout on resize

private:
    QVector<RAGNode> nodes;
    QVector<RAGEdge> edges;
    QVector<int>     deadlockedSet;

    // FIX: store graph dimensions so resizeEvent can re-layout without rebuilding edges
    int storedNumProcesses = 0;
    int storedNumResources = 0;

    void buildNodes(int numProcesses, int numResources);   // FIX: builds nodes from scratch
    void layoutNodes(int numProcesses, int numResources);  // updates positions only
    void drawArrow(QPainter& painter, QPointF from, QPointF to,
                   bool isRequest, bool isDeadlocked);
};

#endif // RAGWIDGET_H
