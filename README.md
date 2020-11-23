    <h1>A C++ Behavior Tree Implementation</h1>
    <h2>The Code</h2>
    <p>
        This is a behavior tree implementation in C++. It uses my 2D game engine, Sloth Engine, for basic rendering and component based 
        actors. This project adds a new component, the AI Component (BehaviorTrees\Game\Source\Logic\Components\AIComponent\AIComponent.h),
        that controls the flow and traversal through the behavior tree. The currently implemented behaviors are:
    </p>
    <ul>
        <li>Idle</li>
        <li>Patrol</li>
        <li>Turn</li>
        <li>Wander</li>
        <li>Chase</li>
        <li>Speak</li>
    </ul>
    <p>The tree structure is defined in XML (BehaviorTrees\Game\Data\guard-scene.xml).</p>
    <h2>The Scene</h2>
    <p>
        The red agent stands in the middle of the screen while a green agent walks a straight path past him. When the red agent sees the green 
        agent (enters vision cone). The agent approaches and they have a short conversation. Then the red agent returns to his post.
    </p>
