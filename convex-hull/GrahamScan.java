import java.awt.*;
import java.awt.Point;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import javax.swing.*;
import java.util.Stack;

public class GrahamScan extends JPanel
{

    private List<Point> points, convexHull;

    public GrahamScan() {
        points = new ArrayList<>();
        convexHull = new ArrayList<>();
        setPreferredSize(new Dimension(600, 600));
        addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                points.add(new Point(e.getX(), e.getY()));
				repaint();
				if(points.size()>=3)
				{
					convexHull = computeConvexHull(points);
					repaint();
				}
            }
        });    

        JFrame frame = new JFrame("Graham Scan");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.add(this);
        frame.pack();
        frame.setVisible(true);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setColor(Color.BLACK);
        for (Point p : points) {
            g.fillOval(p.x - 4, p.y - 4, 8, 8);
        }
        if (!convexHull.isEmpty()) {
            g.setColor(Color.RED);
            Point prev = convexHull.get(convexHull.size() - 1);
            for (Point p : convexHull) {
                g.drawLine(prev.x, prev.y, p.x, p.y);
                prev = p;
            }
        }
    }

    //Graham Scan Algorithm
    private List<Point> computeConvexHull(List<Point> points) {
        
        //If there are not enough points to build the convex hull, return the arraylist as it is
        if (points.size() < 3)
        {
            return new ArrayList<>(points);
        }
    
        Stack<Point> stack = new Stack<>();
        Point minYPoint = getMinY(points);
        sortByAngle(points, minYPoint);
    
        stack.push(points.get(0));
        stack.push(points.get(1));
    
        for (int i = 2, size = points.size(); i < size; i++) {
            Point next = points.get(i);
            Point p = stack.pop();
            while (!stack.isEmpty() && ccw(stack.peek(), p, next) <= 0) {
                p = stack.pop();
            }
            stack.push(p);
            stack.push(next);
        }
    
        List<Point> convexHull = new ArrayList<>(stack);
        convexHull.add(minYPoint);
        return convexHull;
    }
    
    private Point getMinY(List<Point> points)
    {
        //calculating the bottomost point
        Point minY = points.get(0);
        for (Point point : points) {
            if (point.y < minY.y || (point.y == minY.y && point.x < minY.x))
            {
                minY = point;
            }
        }
        return minY;
    }

    private void sortByAngle(List<Point> points, Point ref)
    {
        Collections.sort(points, (b, c) ->
        {
            if (b == ref) return -1;
            if (c == ref) return 1;
            int ccw = ccw(ref, b, c);
            if (ccw == 0) {
                if (Float.compare(b.x, c.x) == 0) {
                    return b.y < c.y ? -1 : 1;                
                } else {
                    return b.x < c.x ? -1 : 1;                
                }                
            } else {
                return ccw * -1;
            }
        });         
    }

    private int ccw(Point a, Point b, Point c)
    //calculating the cross product
    {
		return (int) ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));

    }

    public static void main(String[] args)
    {
        SwingUtilities.invokeLater(() -> new GrahamScan());
    }
}