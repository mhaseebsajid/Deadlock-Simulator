#include "RAGWidget.h"
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QtMath>
#include <QFontMetrics>
#include <QResizeEvent>

RAGWidget::RAGWidget(QWidget* parent) : QWidget(parent) {
    setMinimumSize(300, 300);
    setStyleSheet("background-color: #11111b; border-radius: 8px;");
}

void RAGWidget::clear() {
    nodes.clear();
    edges.clear();
    deadlockedSet.clear();
    update();
}

void RAGWidget::setGraph(int numProcesses, int numResources,
                          const QVector<QVector<int>>& allocation,
                          const QVector<QVector<int>>& request,
                          const QVector<int>& deadlocked)
{
    nodes.clear();
    edges.clear();
    deadlockedSet = deadlocked;

    // FIX: store counts so resizeEvent can re-layout correctly
    storedNumProcesses = numProcesses;
    storedNumResources = numResources;

    buildNodes(numProcesses, numResources);

    // Allocation edges: R → P  (assignment)
    for (int r = 0; r < numResources; r++) {
        for (int p = 0; p < numProcesses; p++) {
            if (r < allocation[p].size() && allocation[p][r] > 0) {
                int rIdx = numProcesses + r;
                edges.append({rIdx, p, false});
            }
        }
    }

    // Request edges: P → R
    for (int p = 0; p < numProcesses; p++) {
        for (int r = 0; r < numResources; r++) {
            if (r < request[p].size() && request[p][r] > 0) {
                int rIdx = numProcesses + r;
                edges.append({p, rIdx, true});
            }
        }
    }

    update();
}

void RAGWidget::layoutNodes(int numProcesses, int numResources)
{
    // Use current widget dimensions; fall back to sensible defaults
    int w = width()  > 10 ? width()  : 600;
    int h = height() > 10 ? height() : 400;

    // Processes in a column on the left
    // Only resize existing nodes — don't add new ones here when called from resizeEvent
    int nodeIdx = 0;
    for (int i = 0; i < numProcesses; i++, nodeIdx++) {
        if (nodeIdx >= nodes.size()) break;
        double yStep = (double)(h - 80) / qMax(numProcesses, 1);
        nodes[nodeIdx].pos = QPointF(w * 0.22, 50 + i * yStep + yStep * 0.5);
    }

    // Resources in a column on the right
    for (int j = 0; j < numResources; j++, nodeIdx++) {
        if (nodeIdx >= nodes.size()) break;
        double yStep = (double)(h - 80) / qMax(numResources, 1);
        nodes[nodeIdx].pos = QPointF(w * 0.78, 50 + j * yStep + yStep * 0.5);
    }
}

// FIX: New helper — builds nodes from scratch (called only by setGraph)
void RAGWidget::buildNodes(int numProcesses, int numResources)
{
    nodes.clear();

    int w = width()  > 10 ? width()  : 600;
    int h = height() > 10 ? height() : 400;

    for (int i = 0; i < numProcesses; i++) {
        RAGNode n;
        n.label = "P" + QString::number(i);
        n.isProcess = true;
        double yStep = (double)(h - 80) / qMax(numProcesses, 1);
        n.pos = QPointF(w * 0.22, 50 + i * yStep + yStep * 0.5);
        nodes.append(n);
    }

    for (int j = 0; j < numResources; j++) {
        RAGNode n;
        n.label = "R" + QString::number(j);
        n.isProcess = false;
        double yStep = (double)(h - 80) / qMax(numResources, 1);
        n.pos = QPointF(w * 0.78, 50 + j * yStep + yStep * 0.5);
        nodes.append(n);
    }
}

void RAGWidget::drawArrow(QPainter& painter, QPointF from, QPointF to,
                           bool isRequest, bool isDeadlocked)
{
    QColor color = isDeadlocked ? QColor("#f38ba8")
                 : isRequest    ? QColor("#fab387")
                                : QColor("#a6e3a1");

    QPen pen(color, 2.0);
    painter.setPen(pen);
    painter.setBrush(color);

    // Shorten line to not overlap node circle/rect
    double dx = to.x() - from.x();
    double dy = to.y() - from.y();
    double len = sqrt(dx*dx + dy*dy);
    if (len < 1) return;
    double ux = dx/len, uy = dy/len;
    double pad = 22;
    QPointF p1 = from + QPointF(ux * pad, uy * pad);
    QPointF p2 = to   - QPointF(ux * pad, uy * pad);

    painter.drawLine(p1, p2);

    // Arrowhead
    double arrowLen = 10, arrowWid = 5;
    QPointF arrowP1 = p2 - QPointF(ux*arrowLen - uy*arrowWid,
                                    uy*arrowLen + ux*arrowWid);
    QPointF arrowP2 = p2 - QPointF(ux*arrowLen + uy*arrowWid,
                                    uy*arrowLen - ux*arrowWid);
    QPolygonF arrowHead;
    arrowHead << p2 << arrowP1 << arrowP2;
    painter.drawPolygon(arrowHead);
}

// ─────────────────────────────────────────────────────
//  FIX: resizeEvent — re-layout nodes on widget resize
//  instead of doing it inside paintEvent every frame
// ─────────────────────────────────────────────────────
void RAGWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    if (!nodes.isEmpty()) {
        layoutNodes(storedNumProcesses, storedNumResources);
    }
}

void RAGWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (nodes.isEmpty()) {
        painter.setPen(QColor("#6c7086"));
        painter.setFont(QFont("Segoe UI", 11));
        painter.drawText(rect(), Qt::AlignCenter,
            "Run Detection to visualize\nResource Allocation Graph");
        return;
    }

    // FIX: removed layoutNodes() call from here — it now lives in resizeEvent()
    //      so positions are stable and not recalculated on every single paint event

    // Draw edges first
    for (auto& e : edges) {
        bool dl = false;
        if (e.isRequest) {
            dl = deadlockedSet.contains(e.from);
        } else {
            dl = deadlockedSet.contains(e.to);
        }
        drawArrow(painter, nodes[e.from].pos, nodes[e.to].pos, e.isRequest, dl);
    }

    // Draw nodes
    QFont font("Segoe UI", 10, QFont::Bold);
    painter.setFont(font);
    int r = 20;

    for (auto& n : nodes) {
        bool isDead = false;
        if (n.isProcess) {
            int pidx = n.label.mid(1).toInt();
            isDead = deadlockedSet.contains(pidx);
        }

        QColor fill = isDead         ? QColor("#f38ba8")
                    : n.isProcess    ? QColor("#89b4fa")
                                     : QColor("#a6e3a1");
        QColor border = fill.darker(130);

        painter.setPen(QPen(border, 2));
        painter.setBrush(fill);

        if (n.isProcess) {
            // Circle for processes
            painter.drawEllipse(n.pos, r, r);
        } else {
            // Square for resources
            painter.drawRect(QRectF(n.pos.x()-r, n.pos.y()-r, r*2, r*2));
        }

        painter.setPen(QColor("#1e1e2e"));
        painter.drawText(QRectF(n.pos.x()-r, n.pos.y()-r, r*2, r*2),
                         Qt::AlignCenter, n.label);
    }

    // Legend
    int lx = 10, ly = height() - 70;
    painter.setFont(QFont("Segoe UI", 9));

    painter.setPen(QPen(QColor("#a6e3a1"), 2));
    painter.drawLine(lx, ly, lx+25, ly);
    painter.setPen(QColor("#cdd6f4"));
    painter.drawText(lx+30, ly+5, "Assignment (R→P)");

    painter.setPen(QPen(QColor("#fab387"), 2));
    painter.drawLine(lx, ly+18, lx+25, ly+18);
    painter.setPen(QColor("#cdd6f4"));
    painter.drawText(lx+30, ly+23, "Request (P→R)");

    painter.setPen(QPen(QColor("#f38ba8"), 2));
    painter.drawLine(lx, ly+36, lx+25, ly+36);
    painter.setPen(QColor("#cdd6f4"));
    painter.drawText(lx+30, ly+41, "Deadlocked");
}
