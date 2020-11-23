#pragma once
/** \file PathedBehavior.h */
// Created by Myles Cardiff

#include <Logic/Components/AIComponent/ActionNode.h>


/// <summary>
/// Holds waypoint and slow down data
/// </summary>
struct Waypoint
{
	slth::Vector2f m_point;
	bool m_slowDown;
};

/// <summary>
/// Base class for any behavior that requires pathfinding to navigate
/// </summary>
class PathedBehavior
	: public ActionNode
{
public:
	
	/// /// <summary>
	/// Default Constructor
	/// </summary>
	PathedBehavior(AIComponent* pOwner);

	/// <summary>
	/// Sets a path using tile indexes as waypoints. The agent will use the grid
	/// to path-find beteween those destinations
	/// </summary>
	/// <param name="rawPath"></param>
	void SetRawPath(std::vector<size_t>& rawPath, bool loop);

	/// <summary>
	/// Move to the next waypoint
	/// </summary>
	/// <returns></returns>
	Waypoint NextWaypoint();

	/// <summary>
	/// Internal path step for pathfinding so that a time-sliced path
	/// can be resumed if it's not found in the alloted time.
	/// </summary>
	void StepPathFind(bool loop);

	/// <summary>
	/// Continues moving the agent along it's already-established path.
	/// </summary>
	/// <param name="deltaTime">Time since last frame</param>
	/// <param name="loop">Does this path loop? This is passed in because 
	/// it, in turn, needs to be passed into the pathing algorithms to set
	/// looping waypoint behavior. </param>
	/// <returns></returns>
	Status MoveAlongPath(float deltaTime, bool loop);

	/// <summary>
	/// Stop and figure out a new path
	/// </summary>
	void Repath(bool loop);


protected:
	// path finding
	// these keep temporary path data from the grid, so we 
	// can continue pathfinding if it takes longer than a frame
	size_t m_lastPathedIndex;
	std::vector<size_t> m_tempRawPath;
	std::vector <slth::Vector2f> m_tempProcessedPath;
	bool m_pathInProgress;
	std::vector<Waypoint> m_waypoints;
	size_t m_currentWaypointTarget;
	float m_arriveThreshold;

	static constexpr float kArrivalDistance = 5.f;
	static constexpr long long kPathTimeAllowed = 5;
	static constexpr float kDefaultArriveThreshold = 1.5f;
	static constexpr float kSlowRadius = 20.f;

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //
	const std::vector<Waypoint>& GetWaypoints() const { return m_waypoints; }

};
