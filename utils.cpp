#include "stdafx.h"
#include <algorithm>
#include <cmath>
#include "utils.h"
#include <vector>

#pragma region OpenGLDrawFunctionality
void utils::SetColor(const Color4f& color)
{
	glColor4f(color.r, color.g, color.b, color.a);
}

void utils::DrawPoint(float x, float y, float pointSize)
{
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	{
		glVertex2f(x, y);
	}
	glEnd();
}

void utils::DrawPoint(const Point2f& p, float pointSize)
{
	DrawPoint(p.x, p.y, pointSize);
}

void utils::DrawPoints(Point2f* pVertices, int nrVertices, float pointSize)
{
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	{
		for (int idx{0}; idx < nrVertices; ++idx)
		{
			glVertex2f(pVertices[idx].x, pVertices[idx].y);
		}
	}
	glEnd();
}

void utils::DrawLine(float x1, float y1, float x2, float y2, float lineWidth)
{
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
	{
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	}
	glEnd();
}

void utils::DrawLine(const Point2f& p1, const Point2f& p2, float lineWidth)
{
	DrawLine(p1.x, p1.y, p2.x, p2.y, lineWidth);
}

void utils::DrawRect(float left, float bottom, float width, float height, float lineWidth)
{
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(left, bottom);
		glVertex2f(left + width, bottom);
		glVertex2f(left + width, bottom + height);
		glVertex2f(left, bottom + height);
	}
	glEnd();
}

void utils::DrawRect(const Point2f& bottomLeft, float width, float height, float lineWidth)
{
	DrawRect(bottomLeft.x, bottomLeft.y, width, height, lineWidth);
}

void utils::DrawRect(const Rectf& rect, float lineWidth)
{
	DrawRect(rect.left, rect.bottom, rect.width, rect.height, lineWidth);
}

void utils::FillRect(float left, float bottom, float width, float height)
{
	glBegin(GL_POLYGON);
	{
		glVertex2f(left, bottom);
		glVertex2f(left + width, bottom);
		glVertex2f(left + width, bottom + height);
		glVertex2f(left, bottom + height);
	}
	glEnd();
}

void utils::FillRect(const Point2f& bottomLeft, float width, float height)
{
	FillRect(bottomLeft.x, bottomLeft.y, width, height);
}

void utils::FillRect(const Rectf& rect)
{
	FillRect(rect.left, rect.bottom, rect.width, rect.height);
}

void utils::DrawEllipse(float centerX, float centerY, float radX, float radY, float lineWidth)
{
	float dAngle{radX > radY ? float(M_PI / radX) : float(M_PI / radY)};

	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	{
		for (float angle = 0.0; angle < float(2 * M_PI + dAngle); angle += dAngle)
		{
			glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
		}
	}
	glEnd();
}

void utils::DrawEllipse(const Point2f& center, float radX, float radY, float lineWidth)
{
	DrawEllipse(center.x, center.y, radX, radY, lineWidth);
}

void utils::DrawEllipse(Ellipsef ellipse, float lineWidth)
{
	DrawEllipse(ellipse.center.x, ellipse.center.y, ellipse.radiusX, ellipse.radiusY, lineWidth);
}

void utils::FillEllipse(float centerX, float centerY, float radX, float radY)
{
	float dAngle{radX > radY ? float(M_PI / radX) : float(M_PI / radY)};

	glBegin(GL_POLYGON);
	{
		for (float angle = 0.0; angle < float(2 * M_PI + dAngle); angle += dAngle)
		{
			glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
		}
	}
	glEnd();
}

void utils::FillEllipse(Ellipsef ellipse)
{
	FillEllipse(ellipse.center.x, ellipse.center.y, ellipse.radiusX, ellipse.radiusY);
}

void utils::FillEllipse(const Point2f& center, float radX, float radY)
{
	FillEllipse(center.x, center.y, radX, radY);
}

void utils::DrawArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle, float lineWidth)
{
	if (fromAngle > tillAngle)
	{
		return;
	}

	float dAngle{radX > radY ? float(M_PI / radX) : float(M_PI / radY)};

	glLineWidth(lineWidth);
	glBegin(GL_LINE_STRIP);
	{
		for (float angle = fromAngle; angle < tillAngle; angle += dAngle)
		{
			glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
		}
		glVertex2f(centerX + radX * float(cos(tillAngle)), centerY + radY * float(sin(tillAngle)));
	}
	glEnd();
}

void utils::DrawArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle, float lineWidth)
{
	DrawArc(center.x, center.y, radX, radY, fromAngle, tillAngle, lineWidth);
}

void utils::FillArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle)
{
	if (fromAngle > tillAngle)
	{
		return;
	}
	float dAngle{radX > radY ? float(M_PI / radX) : float(M_PI / radY)};

	glBegin(GL_POLYGON);
	{
		glVertex2f(centerX, centerY);
		for (float angle = fromAngle; angle < tillAngle; angle += dAngle)
		{
			glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
		}
		glVertex2f(centerX + radX * float(cos(tillAngle)), centerY + radY * float(sin(tillAngle)));
	}
	glEnd();
}

void utils::FillArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle)
{
	FillArc(center.x, center.y, radX, radY, fromAngle, tillAngle);
}

void utils::DrawPolygon(const std::vector<Point2f>& vertices, bool closed, float lineWidth)
{
	DrawPolygon(vertices.data(), vertices.size(), closed, lineWidth);
}

void utils::DrawPolygon(const Point2f* pVertices, size_t nrVertices, bool closed, float lineWidth)
{
	glLineWidth(lineWidth);
	closed ? glBegin(GL_LINE_LOOP) : glBegin(GL_LINE_STRIP);
	{
		for (size_t idx{0}; idx < nrVertices; ++idx)
		{
			glVertex2f(pVertices[idx].x, pVertices[idx].y);
		}
	}
	glEnd();
}

void utils::FillPolygon(const std::vector<Point2f>& vertices)
{
	FillPolygon(vertices.data(), vertices.size());
}

void utils::FillPolygon(const Point2f* pVertices, size_t nrVertices)
{
	glBegin(GL_POLYGON);
	{
		for (size_t idx{0}; idx < nrVertices; ++idx)
		{
			glVertex2f(pVertices[idx].x, pVertices[idx].y);
		}
	}
	glEnd();
}
#pragma endregion OpenGLDrawFunctionality

#pragma region CollisionFunctionality
float DistPointLineSegment(const Point2f& p, const Point2f& a, const Point2f& b);
bool IsPointOnLineSegment(const Point2f& p, const Point2f& a, const Point2f& b);

bool utils::IsPointInRect(const Point2f& p, const Rectf& r)
{
	return p.x >= r.left && p.x <= r.left + r.width &&
		p.y >= r.bottom && p.y <= r.bottom + r.height;
}

bool utils::IsPointInCircle(const Point2f& p, const Circlef& c)
{
	float squaredDist = (p.x - c.center.x) * (p.x - c.center.x) + (p.y - c.center.y) * (p.y - c.center.y);
	float squaredRadius = c.radius * c.radius;
	return squaredRadius >= squaredDist;
}


bool utils::IsOverlapping(const Point2f& a, const Point2f& b, const Rectf& r)
{
	// if one of the line segment end points is in the rect
	if (IsPointInRect(a, r) || IsPointInRect(b, r))
	{
		return true;
	}

	HitInfo hitInfo{};
	Point2f vertices[]{Point2f{r.left, r.bottom},
		Point2f{r.left + r.width, r.bottom},
		Point2f{r.left + r.width, r.bottom + r.height},
		Point2f{r.left, r.bottom + r.height}};

	return Raycast(vertices, 4, a, b, hitInfo);
}

bool utils::IsOverlapping(const Rectf& r1, const Rectf& r2)
{
	// If one rectangle is on left side of the other
	if (r1.left + r1.width < r2.left || r2.left + r2.width < r1.left)
	{
		return false;
	}

	// If one rectangle is under the other
	if (r1.bottom > r2.bottom + r2.height || r2.bottom > r1.bottom + r1.height)
	{
		return false;
	}

	return true;
}

bool utils::IsOverlapping(const Rectf& r, const Circlef& c)
{
	// Is center of circle in the rectangle?
	if (IsPointInRect(c.center, r))return true;

	// Check line segments
	if (DistPointLineSegment(c.center, {r.left, r.bottom}, {r.left, r.bottom + r.height}) <= c.radius) return true;
	if (DistPointLineSegment(c.center, {r.left, r.bottom}, {r.left + r.width, r.bottom}) <= c.radius) return true;
	if (DistPointLineSegment(c.center, {r.left + r.width, r.bottom + r.height}, {r.left, r.bottom + r.height}) <= c.radius) return true;
	if (DistPointLineSegment(c.center, {r.left + r.width, r.bottom + r.height}, {r.left + r.width, r.bottom}) <= c.radius) return true;
	return false;
}

bool utils::IsOverlapping(const Circlef& c1, const Circlef& c2)
{
	// squared distance between centers
	float xDistance{c1.center.x - c2.center.x};
	float yDistance{c1.center.y - c2.center.y};
	float squaredDistance = xDistance * xDistance + yDistance * yDistance;

	float squaredTouchingDistance = (c1.radius + c2.radius) * (c1.radius + c2.radius);
	if (squaredDistance < squaredTouchingDistance)
	{
		return true;
	}
	return false;
}

bool utils::IsOverlapping(const Point2f& a, const Point2f& b, const Circlef& c)
{
	return DistPointLineSegment(c.center, a, b) <= c.radius;
}

bool utils::IsOverlapping(const std::vector<Point2f>& vertices, const Circlef& c)
{
	return IsOverlapping(vertices.data(), vertices.size(), c);
}

bool utils::IsOverlapping(std::vector<Point2f> vertices, const Rectf& c)
{
	Point2f leftBottom{c.left,c.bottom};
	Point2f leftTop{c.left, c.bottom + c.height};
	Point2f rightBottom{c.left + c.width, c.bottom};
	Point2f rightTop{c.left + c.width, c.bottom + c.height};

	if (IsPointInPolygon(leftBottom, vertices))
	{
		return true;
	}
	if (IsPointInPolygon(leftTop, vertices))
	{
		return true;
	}
	if (IsPointInPolygon(rightBottom, vertices))
	{
		return true;
	}
	if (IsPointInPolygon(rightTop, vertices)) return true;

	float a;
	float b;

	// Check overlapping line segments with circle
	for (size_t i = 0; i < vertices.size() - 1; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (!IntersectLineSegments(vertices[i], vertices[i + 1], leftBottom, leftTop, a, b))
			{
				return true;
			}
			if (!IntersectLineSegments(vertices[i], vertices[i + 1], leftBottom, rightBottom, a, b))
			{
				return true;
			}
			if (!IntersectLineSegments(vertices[i], vertices[i + 1], rightBottom, rightTop, a, b))
			{
				return true;
			}
			if (!IntersectLineSegments(vertices[i], vertices[i + 1], rightTop, leftTop, a, b))
			{
				return true;
			}
		}
	}

	return false;
}

bool utils::IsOverlapping(const Point2f* vertices, size_t nrVertices, const Circlef& c)
{
	// Check points in circle
	for (size_t i{0}; i < nrVertices; ++i)
	{
		if (IsPointInCircle(vertices[i], c))
		{
			return true;
		}
	}

	// Check overlapping line segments with circle
	for (size_t i{0}; i < nrVertices; ++i)
	{
		if (DistPointLineSegment(c.center, vertices[i], vertices[(i + 1) % nrVertices]) <= c.radius)
		{
			return true;
		}
	}

	// No overlapping line segments, verify whether circle is inside polygon
	if (IsPointInPolygon(c.center, vertices, nrVertices))
	{
		return true;
	}
	return false;
}

bool utils::IsPointInPolygon(const Point2f& p, const std::vector<Point2f>& vertices)
{
	return IsPointInPolygon(p, vertices.data(), vertices.size());
}

bool utils::IsPointInPolygon(const Point2f& p, const Point2f* vertices, size_t nrVertices)
{
	if (nrVertices < 2)
	{
		return false;
	}
	// 1. First do a simple test with axis aligned bounding box around the polygon
	float xMin{vertices[0].x};
	float xMax{vertices[0].x};
	float yMin{vertices[0].y};
	float yMax{vertices[0].y};
	for (size_t idx{1}; idx < nrVertices; ++idx)
	{
		if (xMin > vertices[idx].x)
			xMin = vertices[idx].x;
		if (xMax < vertices[idx].x)
			xMax = vertices[idx].x;
		if (yMin > vertices[idx].y)
			yMin = vertices[idx].y;
		if (yMax < vertices[idx].y)
			yMax = vertices[idx].y;
	}
	if (p.x < xMin || p.x > xMax || p.y < yMin || p.y > yMax)
		return false;

	// 2. Draw a virtual ray from anywhere outside the polygon to the point 
	//    and count how often it hits any side of the polygon. 
	//    If the number of hits is even, it's outside of the polygon, if it's odd, it's inside.
	int numberOfIntersectionPoints{0};
	Point2f p2{xMax + 10.0f, p.y}; // Horizontal line from point to point outside polygon (p2)

	// Count the number of intersection points
	float lambda1{}, lambda2{};
	for (size_t i{0}; i < nrVertices; ++i)
	{
		if (IntersectLineSegments(vertices[i], vertices[(i + 1) % nrVertices], p, p2, lambda1, lambda2))
		{
			if (lambda1 > 0 && lambda1 <= 1 && lambda2 > 0 && lambda2 <= 1)
			{
				++numberOfIntersectionPoints;
			}
		}
	}
	if (numberOfIntersectionPoints % 2 == 0)
		return false;
	return true;
}

bool utils::IntersectLineSegments(const Point2f& p1, const Point2f& p2, const Point2f& q1, const Point2f& q2, float& outLambda1, float& outLambda2, float epsilon)
{
	bool intersecting{false};

	Vector2f p1p2{p1, p2};
	Vector2f q1q2{q1, q2};

	// cross product to determine if parallel
	float denom = p1p2.CrossProduct(q1q2);

	// Don't divide by zero
	if (abs(denom) > epsilon)
	{
		intersecting = true;

		Vector2f p1q1{p1, q1};

		float num1 = p1q1.CrossProduct(q1q2);
		float num2 = p1q1.CrossProduct(p1p2);
		outLambda1 = num1 / denom;
		outLambda2 = num2 / denom;
	}
	else // are parallel
	{
		//connect start points
		Vector2f p1q1{p1, q1};

		// cross product to determine if segments and the line connecting their start points are parallel, 
		// if so, than they are on a line
		// if not, then there is no intersection
		float denom = p1q1.CrossProduct(q1q2);
		if (abs(denom) > epsilon) return false;

		// check the 4 conditions
		outLambda1 = 0;
		outLambda2 = 0;
		if (IsPointOnLineSegment(p1, q1, q2))intersecting = true;
		if (IsPointOnLineSegment(p2, q1, q2))intersecting = true;
		if (IsPointOnLineSegment(q1, p1, p2))intersecting = true;
		if (IsPointOnLineSegment(q2, p1, p2))intersecting = true;
	}
	return intersecting;
}

bool utils::Raycast(const std::vector<Point2f>& vertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo)
{
	return Raycast(vertices.data(), vertices.size(), rayP1, rayP2, hitInfo);
}

bool utils::Raycast(const std::vector<Point2f>& vertices, Rectf& rayRect, Vector2f& actorVelocity)
{
	HitInfo hitInfo;

	Point2f rectMiddleLeft{rayRect.left, rayRect.bottom + rayRect.height / 2};
	Point2f rectMiddleRight{rayRect.left + rayRect.width, rayRect.bottom + rayRect.height / 2};
	bool hit = Raycast(vertices.data(), vertices.size(), rectMiddleLeft, rectMiddleRight, hitInfo);

	if (hit)
	{
		if (hitInfo.normal.x <= 0)
		{
			rayRect.left = hitInfo.intersectPoint.x - rayRect.width;
		}
		else
		{
			rayRect.left = hitInfo.intersectPoint.x;
		}
		actorVelocity.x = 0;
	}

	HitInfo hitInfo02;
	Point2f rectMiddleDown{rayRect.left + rayRect.width / 2, rayRect.bottom};
	Point2f rectMiddleUp{rayRect.left + rayRect.width / 2, rayRect.bottom + rayRect.height};
	bool hit02 = Raycast(vertices.data(), vertices.size(), rectMiddleDown, rectMiddleUp, hitInfo02);

	if (hit02)
	{
		if (hitInfo02.normal.y <= 0)
		{
			rayRect.bottom = hitInfo02.intersectPoint.y - rayRect.height - 1;
		}
		else
		{
			rayRect.bottom = hitInfo02.intersectPoint.y;
		}
		actorVelocity.y = 0;
	}

	//utils::HitInfo hitInfo03;
	//Point2f bottomLeft{ rayRect.left, rayRect.bottom };
	//Point2f topRight{ rayRect.left + rayRect.width , rayRect.bottom + rayRect.height };
	//bool hit03 = Raycast(vertices.data(), vertices.size(), bottomLeft, topRight, hitInfo03);

	//if (hit03)
	//{
	// if (hitInfo03.normal.y <= 0)
	// {
	//	 rayRect.bottom = hitInfo03.intersectPoint.y - rayRect.height - 1;
	// }
	// else
	// {
	//	 rayRect.bottom = hitInfo03.intersectPoint.y;
	// }
	// actorVelocity.y = 0;
	//}


	return hit || hit02;
}

bool utils::Raycast(const Point2f* vertices, const size_t nrVertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo)
{
	if (nrVertices == 0)
	{
		return false;
	}

	std::vector<HitInfo> hits;

	Rectf r1, r2;
	// r1: minimal AABB rect enclosing the ray
	r1.left = std::min(rayP1.x, rayP2.x);
	r1.bottom = std::min(rayP1.y, rayP2.y);
	r1.width = std::max(rayP1.x, rayP2.x) - r1.left;
	r1.height = std::max(rayP1.y, rayP2.y) - r1.bottom;

	// Line-line intersections.
	for (size_t idx{0}; idx <= nrVertices; ++idx)
	{
		// Consider line segment between 2 consecutive vertices
		// (modulo to allow closed polygon, last - first vertice)
		Point2f q1 = vertices[(idx + 0) % nrVertices];
		Point2f q2 = vertices[(idx + 1) % nrVertices];

		// r2: minimal AABB rect enclosing the 2 vertices
		r2.left = std::min(q1.x, q2.x);
		r2.bottom = std::min(q1.y, q2.y);
		r2.width = std::max(q1.x, q2.x) - r2.left;
		r2.height = std::max(q1.y, q2.y) - r2.bottom;

		if (IsOverlapping(r1, r2))
		{
			float lambda1{};
			float lambda2{};
			if (IntersectLineSegments(rayP1, rayP2, q1, q2, lambda1, lambda2))
			{
				if (lambda1 > 0 && lambda1 <= 1 && lambda2 > 0 && lambda2 <= 1)
				{
					HitInfo hitInfo;
					hitInfo.lambda = lambda1;
					hitInfo.intersectPoint = {rayP1.x + (rayP2.x - rayP1.x) * lambda1, rayP1.y + (rayP2.y - rayP1.y) * lambda1};
					hitInfo.normal = Vector2f{q2 - q1}.Orthogonal().Normalized();
					hits.push_back(hitInfo);
				}
			}
		}
	}

	if (hits.size() == 0)
	{
		return false;
	}

	// Get closest intersection point and copy it into the hitInfo parameter
	hitInfo = *std::min_element(hits.begin(), hits.end(),
	                            []( const HitInfo& first, const HitInfo& last )
                            {
	                            return first.lambda < last.lambda;
                            });
	return true;
}


bool IsPointOnLineSegment(const Point2f& p, const Point2f& a, const Point2f& b)
{
	Vector2f ap{a, p}, bp{b, p};
	// If not on same line, return false
	if (abs(ap.CrossProduct(bp)) > 0.001f)
	{
		return false;
	}

	// Both vectors must point in opposite directions if p is between p1 and p2
	if (ap.DotProduct(bp) > 0)
	{
		return false;
	}

	return true;
}

float DistPointLineSegment(const Point2f& p, const Point2f& a, const Point2f& b)
{
	Vector2f ba{a, b};
	Vector2f pa{a, p};
	Vector2f normba = ba.Normalized();
	float distToA = normba.DotProduct(pa);
	// if distToA is negative, then the closest point is A
	// return the distance a, p
	if (distToA < 0)
	{
		return Vector2f{a, p}.Length();
	}
	// if distToA is > than dist(a,b) then the closest point is B
	// return the distance b, p
	float distAB = Vector2f{a, b}.Length();
	if (distToA > distAB)
	{
		return Vector2f{b, p}.Length();
	}

	//closest point is between A and B, calc intersection point
	Vector2f intersection = normba.DotProduct(pa) * normba + a;
	return Vector2f{p - intersection}.Length();
}
#pragma endregion CollisionFunctionality
