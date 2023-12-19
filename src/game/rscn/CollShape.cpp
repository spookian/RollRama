namespace rcoll
{
	static bool Interval::intersects(float aa, float ab, float ba, float bb)
	{
		return (ab < ba) || (bb < aa);
	}

	bool testAxes(CollPointList& a_set, CollPointList& b_set, CollPointList& axes_list)
	{
		for (int i = 0; i < axes_list.num_points; i++)
		{
			float a_min = 99999.9f, a_max = 0.0f;
			float b_min = 99999.9f, b_max = 0.0f;
			Vector3* cur_axis = &axes_list[i];

			for (int j = 0; j < a_set.num_points; j++) // get min max of a_set
			{
				float cur_val = a_set.points[j].dot(*cur_axis); // project vertices onto axis
				if (a_max < cur_val) a_max = cur_val;
				if (a_min > cur_val) a_min = cur_val;
			}

			for (int j = 0; j < b_set.num_points; j++)
			{
				float cur_val = b_set.points[j].dot(*cur_axis);
				if (b_max < cur_val) b_max = cur_val;
				if (b_min > cur_val) b_min = cur_val;
			}

			if (!Interval::intersects(min_a, max_a, min_b, max_b)) // if there is an axis between the two convex shapes, return
			{
				return false;
			}
		}

		return true;
	}

	CollShape::CollisionInfo CollShape::checkCollision(const CollShape& other)
	{
		CollisionInfo result;

		CollPointList this_points = this->getPoints(other);
		CollPointList other_points = other.getPoints(this);
		CollPointList this_normals = this->getNormals(other);
		CollPointList other_normals = other.getNormals(this);
		// i calculated that there is a total of 720 bytes being used here and i don't like that, not one bit.
		result.collided = testAxes(this_points, other_points, this_normals) && testAxes(this_points, other_points, other_normals);
		if (result.collided)
		{
			//calculate MTV
		}
		
		return result;
	}
}