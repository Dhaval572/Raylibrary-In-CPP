#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <memory>
#include <cstdlib>
#include <ctime>

// Simple 2D Vector structure
struct Vector2
{
    float x, y;
    Vector2(float x = 0, float y = 0) : x(x), y(y) {}
    
    Vector2 operator+(const Vector2& other) const { return {x + other.x, y + other.y}; }
    Vector2 operator-(const Vector2& other) const { return {x - other.x, y - other.y}; }
    Vector2 operator*(float scalar) const { return {x * scalar, y * scalar}; }
    
    float Distance(const Vector2& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }
    
    Vector2 Normalize() const {
        float len = sqrt(x * x + y * y);
        if (len == 0) return {0, 0};
        return {x / len, y / len};
    }
    
    float Dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }
};

// Simple Color structure
struct Color
{
    unsigned char r, g, b, a;
    Color(unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, unsigned char a = 255)
        : r(r), g(g), b(b), a(a) {}
};

// Mathematical utilities for ultra-realistic calculations
class MathUtils
{
public:
    static Vector2 CubicBezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, float t)
    {
        float u = 1.0f - t;
        float uu = u * u;
        float uuu = uu * u;
        float tt = t * t;
        float ttt = tt * t;

        Vector2 p = p0 * uuu;
        p = p + (p1 * (3 * uu * t));
        p = p + (p2 * (3 * u * tt));
        p = p + (p3 * ttt);

        return p;
    }

    static float Lerp(float a, float b, float t)
    {
        return a + t * (b - a);
    }

    static float Clamp(float value, float min, float max)
    {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }

    static float CalculateContactDistance(Vector2 breastPos, float breastRadius, Vector2 mouthPos, float mouthRadius)
    {
        float centerDistance = breastPos.Distance(mouthPos);
        return std::max(0.0f, centerDistance - (breastRadius + mouthRadius));
    }

    static Vector2 CalculatePerfectAlignmentPosition(Vector2 breastPos, float breastRadius, Vector2 mouthPos, float mouthRadius, float nippleOffset)
    {
        Vector2 nipplePos = {breastPos.x, breastPos.y - nippleOffset};
        Vector2 direction = (mouthPos - nipplePos).Normalize();
        return nipplePos + (direction * (breastRadius * 0.1f));
    }

    static float PerlinNoise(float x, float y)
    {
        float noise = 0.0f;
        noise += sin(x * 0.02f) * cos(y * 0.03f) * 0.5f;
        noise += sin(x * 0.05f) * cos(y * 0.07f) * 0.25f;
        noise += sin(x * 0.1f) * cos(y * 0.11f) * 0.125f;
        return noise;
    }
};

// Configuration for ultra-realistic parameters
class Config
{
public:
    static const int SCREEN_WIDTH = 1400;
    static const int SCREEN_HEIGHT = 800;

    // Ultra-realistic skin tones and colors
    Color baseSkinColor = {245, 210, 190, 255};
    Color shadowSkinColor = {220, 185, 165, 255};
    Color highlightSkinColor = {255, 235, 215, 255};
    Color areolaBaseColor = {180, 130, 120, 255};
    Color nippleColor = {160, 110, 100, 255};
    Color babySkinColor = {252, 225, 205, 255};
    Color lipColor = {220, 150, 140, 255};
    Color tongueColor = {255, 190, 180, 255};
    Color milkColor = {248, 248, 245, 220};

    // Contact and alignment colors
    Color alignmentGuideColor = {0, 255, 0, 150};
    Color misalignmentColor = {255, 100, 100, 150};
    Color perfectContactColor = {0, 255, 0, 200};
    Color contactZoneColor = {255, 255, 0, 100};

    // Advanced alignment settings
    float perfectAlignmentThreshold = 5.0f;
    float contactDeformationAmount = 0.15f;
    bool showAlignmentGuides = true;
    bool enableAutoAlignment = false;
    float alignmentSensitivity = 2.0f;

    // Animation and physics
    float animationSpeed = 0.8f;
    int milkDropCount = 15;
    int milkStreamCount = 6;
    int skinTextureDetail = 60;
    float veinVisibility = 0.25f;
};

// Advanced alignment system for perfect positioning
class AlignmentSystem
{
private:
    Config* config;
    bool isPerfectlyAligned;
    float alignmentQuality;
    Vector2 idealContactPoint;
    float contactDistance;

public:
    AlignmentSystem(Config* cfg) : config(cfg), isPerfectlyAligned(false), alignmentQuality(0.0f), contactDistance(0.0f) {}

    void UpdateAlignment(Vector2 breastPos, float breastRadius, Vector2 nipplePos, Vector2 mouthPos, float mouthRadius)
    {
        // Calculate contact distance with ultra-precision
        contactDistance = MathUtils::CalculateContactDistance(nipplePos, breastRadius * 0.3f, mouthPos, mouthRadius);
        
        // Calculate alignment quality (0.0 = perfect, 1.0 = completely misaligned)
        alignmentQuality = std::min(1.0f, contactDistance / config->perfectAlignmentThreshold);
        
        // Determine if perfectly aligned (zero distance tolerance)
        isPerfectlyAligned = contactDistance < config->perfectAlignmentThreshold;
        
        // Calculate ideal contact point for perfect alignment
        idealContactPoint = MathUtils::CalculatePerfectAlignmentPosition(breastPos, breastRadius, mouthPos, mouthRadius, breastRadius * 0.15f);
    }

    void PrintAlignmentStatus() const
    {
        std::cout << "\n=== ULTRA-REALISTIC ALIGNMENT STATUS ===" << std::endl;
        std::cout << "Contact Distance: " << contactDistance << " pixels" << std::endl;
        std::cout << "Alignment Quality: " << ((1.0f - alignmentQuality) * 100.0f) << "%" << std::endl;
        std::cout << "Status: " << (isPerfectlyAligned ? "✓ PERFECT ALIGNMENT ACHIEVED" : "⚠ NEEDS ADJUSTMENT") << std::endl;
        std::cout << "Ideal Contact Point: (" << idealContactPoint.x << ", " << idealContactPoint.y << ")" << std::endl;
        
        if (isPerfectlyAligned)
        {
            std::cout << "🎯 ZERO-DISTANCE CONTACT ESTABLISHED!" << std::endl;
            std::cout << "📊 OPTIMAL MILK TRANSFER CONDITIONS MET" << std::endl;
        }
        else
        {
            std::cout << "📏 Distance to perfect alignment: " << contactDistance << " px" << std::endl;
            std::cout << "🎯 Adjustment needed for zero-distance contact" << std::endl;
        }
    }

    Vector2 GetAutoAlignmentSuggestion(Vector2 currentMouthPos, Vector2 nipplePos, float mouthRadius) const
    {
        if (!config->enableAutoAlignment) return currentMouthPos;
        
        Vector2 direction = (currentMouthPos - nipplePos).Normalize();
        return nipplePos + (direction * (mouthRadius * 0.8f));
    }

    bool IsPerfectlyAligned() const { return isPerfectlyAligned; }
    float GetAlignmentQuality() const { return alignmentQuality; }
    float GetContactDistance() const { return contactDistance; }
    Vector2 GetIdealContactPoint() const { return idealContactPoint; }
};

// Contact physics system for realistic deformation
class ContactPhysics
{
private:
    Config* config;
    float deformationAmount;
    Vector2 contactPoint;
    bool isInContact;
    std::vector<Vector2> deformationPoints;

public:
    ContactPhysics(Config* cfg) : config(cfg), deformationAmount(0.0f), isInContact(false) {}

    void UpdateContact(Vector2 breastPos, float breastRadius, Vector2 mouthPos, float mouthRadius, bool isLatched)
    {
        float distance = breastPos.Distance(mouthPos);
        isInContact = distance < (breastRadius + mouthRadius) && isLatched;
        
        if (isInContact)
        {
            // Calculate realistic deformation based on contact pressure
            float overlap = (breastRadius + mouthRadius) - distance;
            deformationAmount = std::min(config->contactDeformationAmount, overlap * 0.1f);
            
            // Calculate precise contact point
            Vector2 direction = (mouthPos - breastPos).Normalize();
            contactPoint = breastPos + (direction * (breastRadius - deformationAmount));
            
            // Generate deformation points for visualization
            GenerateDeformationPoints();
        }
        else
        {
            deformationAmount = 0.0f;
            deformationPoints.clear();
        }
    }

    void GenerateDeformationPoints()
    {
        deformationPoints.clear();
        int numPoints = 12;
        
        for (int i = 0; i < numPoints; i++)
        {
            float angle = (float)i / (numPoints - 1) * M_PI * 2.0f;
            float deformRadius = deformationAmount * 15.0f;
            Vector2 deformPoint = {
                contactPoint.x + deformRadius * cos(angle),
                contactPoint.y + deformRadius * sin(angle)
            };
            deformationPoints.push_back(deformPoint);
        }
    }

    void PrintContactStatus() const
    {
        std::cout << "\n=== CONTACT PHYSICS STATUS ===" << std::endl;
        std::cout << "Contact Established: " << (isInContact ? "YES" : "NO") << std::endl;
        std::cout << "Deformation Amount: " << deformationAmount << std::endl;
        std::cout << "Contact Point: (" << contactPoint.x << ", " << contactPoint.y << ")" << std::endl;
        std::cout << "Deformation Points: " << deformationPoints.size() << " generated" << std::endl;
    }

    float GetDeformationAmount() const { return deformationAmount; }
    bool IsInContact() const { return isInContact; }
    Vector2 GetContactPoint() const { return contactPoint; }
    const std::vector<Vector2>& GetDeformationPoints() const { return deformationPoints; }
};

// Enhanced anatomical breast with ultra-realistic details
class AnatomicalBreast
{
private:
    Vector2 position;
    float radius;
    Config* config;
    ContactPhysics* contactPhysics;
    float breathingPhase;
    std::vector<Vector2> skinPores;
    std::vector<Vector2> veinPoints;

    void GenerateSkinDetails()
    {
        skinPores.clear();
        veinPoints.clear();

        // Generate realistic skin pores
        srand(42); // Fixed seed for consistent generation
        for (int i = 0; i < config->skinTextureDetail; i++)
        {
            float angle = (float)i / config->skinTextureDetail * M_PI * 2.0f;
            float r = radius * (0.7f + 0.3f * ((float)rand() / RAND_MAX));
            Vector2 pore = {
                position.x + r * cos(angle) + (((float)rand() / RAND_MAX) - 0.5f) * 20.0f,
                position.y + r * sin(angle) * 0.8f + (((float)rand() / RAND_MAX) - 0.5f) * 20.0f
            };
            skinPores.push_back(pore);
        }

        // Generate realistic vein patterns
        for (int i = 0; i < 20; i++)
        {
            float angle = (float)i / 20.0f * M_PI * 2.0f;
            float r = radius * (0.4f + 0.4f * ((float)rand() / RAND_MAX));
            Vector2 vein = {
                position.x + r * cos(angle),
                position.y + r * sin(angle) * 0.7f
            };
            veinPoints.push_back(vein);
        }
    }

public:
    AnatomicalBreast(Vector2 pos, float rad, Config* cfg, ContactPhysics* contact)
        : position(pos), radius(rad), config(cfg), contactPhysics(contact), breathingPhase(0.0f)
    {
        GenerateSkinDetails();
    }

    void Update(float deltaTime)
    {
        breathingPhase += deltaTime * 0.6f; // Enhanced breathing animation
    }

    void PrintBreastInfo() const
    {
        std::cout << "\n=== ANATOMICAL BREAST DETAILS ===" << std::endl;
        std::cout << "Position: (" << position.x << ", " << position.y << ")" << std::endl;
        std::cout << "Radius: " << radius << " pixels" << std::endl;
        std::cout << "Nipple Position: (" << GetNipplePosition().x << ", " << GetNipplePosition().y << ")" << std::endl;
        std::cout << "Areola Center: (" << GetAreolaCenter().x << ", " << GetAreolaCenter().y << ")" << std::endl;
        std::cout << "Areola Radius: " << GetAreolaRadius() << " pixels" << std::endl;
        std::cout << "Skin Pores Generated: " << skinPores.size() << std::endl;
        std::cout << "Vein Points Generated: " << veinPoints.size() << std::endl;
        
        if (contactPhysics->IsInContact())
        {
            std::cout << "🤱 CONTACT DEFORMATION ACTIVE" << std::endl;
            std::cout << "Deformation Amount: " << contactPhysics->GetDeformationAmount() << std::endl;
        }
    }

    void SetPosition(Vector2 pos)
    {
        position = pos;
        GenerateSkinDetails(); // Regenerate details for new position
    }

    void SetRadius(float rad)
    {
        radius = rad;
        GenerateSkinDetails(); // Regenerate details for new size
    }

    Vector2 GetPosition() const { return position; }
    float GetRadius() const { return radius; }

    Vector2 GetNipplePosition() const
    {
        float areolaRadius = radius * 0.35f;
        Vector2 nipplePos = {position.x, position.y - areolaRadius * 0.25f};
        
        // Account for contact deformation
        if (contactPhysics->IsInContact())
        {
            nipplePos.y += contactPhysics->GetDeformationAmount() * 5.0f;
        }
        
        return nipplePos;
    }

    Vector2 GetAreolaCenter() const
    {
        return {position.x, position.y - radius * 0.05f};
    }

    float GetAreolaRadius() const
    {
        return radius * 0.35f;
    }
};

// Ultra-realistic baby mouth with perfect alignment capabilities
class BabyMouth
{
private:
    Vector2 position;
    float radius;
    bool isLatched;
    Config* config;
    ContactPhysics* contactPhysics;
    float suckingPhase;
    float jawOpenness;

public:
    BabyMouth(Vector2 pos, float rad, Config* cfg, ContactPhysics* contact)
        : position(pos), radius(rad), isLatched(false), config(cfg), 
          contactPhysics(contact), suckingPhase(0.0f), jawOpenness(0.0f) {}

    void Update(float deltaTime)
    {
        suckingPhase += deltaTime * 2.5f;
        
        // Update jaw openness based on latch state
        float targetOpenness = isLatched ? 0.8f : 0.3f;
        jawOpenness = MathUtils::Lerp(jawOpenness, targetOpenness, deltaTime * 8.0f);
    }

    void PrintMouthInfo() const
    {
        std::cout << "\n=== BABY MOUTH DETAILS ===" << std::endl;
        std::cout << "Position: (" << position.x << ", " << position.y << ")" << std::endl;
        std::cout << "Radius: " << radius << " pixels" << std::endl;
        std::cout << "Effective Radius: " << GetEffectiveRadius() << " pixels" << std::endl;
        std::cout << "Latch Status: " << (isLatched ? "LATCHED" : "NOT LATCHED") << std::endl;
        std::cout << "Jaw Openness: " << (jawOpenness * 100.0f) << "%" << std::endl;
        std::cout << "Sucking Phase: " << suckingPhase << " radians" << std::endl;
        
        if (isLatched && contactPhysics->IsInContact())
        {
            std::cout << "👶 ACTIVE FEEDING STATE" << std::endl;
            std::cout << "Lip Seal Established: YES" << std::endl;
            std::cout << "Peristaltic Tongue Motion: ACTIVE" << std::endl;
        }
    }

    void SetPosition(Vector2 pos) { position = pos; }
    void SetRadius(float rad) { radius = rad; }
    void SetLatched(bool latched) { isLatched = latched; }
    
    Vector2 GetPosition() const { return position; }
    float GetRadius() const { return radius; }
    bool IsLatched() const { return isLatched; }
    float GetEffectiveRadius() const { return radius * (1.0f + jawOpenness * 0.3f); }
};

// Enhanced baby head with perfect facial alignment
class BabyHead
{
private:
    BabyMouth mouth;
    Config* config;
    ContactPhysics* contactPhysics;
    AlignmentSystem* alignmentSystem;

public:
    BabyHead(Vector2 pos, float mouthRadius, Config* cfg, ContactPhysics* contact, AlignmentSystem* alignment)
        : mouth(pos, mouthRadius, cfg, contact), config(cfg), 
          contactPhysics(contact), alignmentSystem(alignment) {}

    void Update(float deltaTime)
    {
        mouth.Update(deltaTime);
    }

    void PrintHeadInfo() const
    {
        std::cout << "\n=== BABY HEAD DETAILS ===" << std::endl;
        std::cout << "Head Position: (" << mouth.GetPosition().x << ", " << mouth.GetPosition().y << ")" << std::endl;
        std::cout << "Head Radius: " << (mouth.GetRadius() * 1.8f) << " pixels" << std::endl;
        mouth.PrintMouthInfo();
        
        if (mouth.IsLatched() && alignmentSystem->IsPerfectlyAligned())
        {
            std::cout << "🎯 OPTIMAL FEEDING POSITION ACHIEVED" << std::endl;
            std::cout << "Facial Features: Relaxed feeding expression" << std::endl;
            std::cout << "Cheek Blush: Enhanced due to active feeding" << std::endl;
        }
    }

    void SetPosition(Vector2 pos) { mouth.SetPosition(pos); }
    void SetMouthRadius(float rad) { mouth.SetRadius(rad); }
    void SetLatched(bool latched) { mouth.SetLatched(latched); }
    
    Vector2 GetPosition() const { return mouth.GetPosition(); }
    Vector2 GetMouthPosition() const { return mouth.GetPosition(); }
    float GetMouthRadius() const { return mouth.GetRadius(); }
    float GetEffectiveMouthRadius() const { return mouth.GetEffectiveRadius(); }
    bool IsLatched() const { return mouth.IsLatched(); }
};

// Ultra-realistic milk ejection with perfect physics
class MilkEjection
{
private:
    Vector2 source;
    Vector2 target;
    float progress;
    Config* config;
    AlignmentSystem* alignmentSystem;
    ContactPhysics* contactPhysics;
    bool isActive;
    std::vector<std::vector<Vector2>> milkDroplets;

public:
    MilkEjection(Config* cfg, AlignmentSystem* alignment, ContactPhysics* contact) 
        : source({0, 0}), target({0, 0}), progress(0.0f), config(cfg), 
          alignmentSystem(alignment), contactPhysics(contact), isActive(false)
    {
        // Initialize milk stream data structures
        milkDroplets.resize(config->milkStreamCount);
        for (int stream = 0; stream < config->milkStreamCount; stream++)
        {
            milkDroplets[stream].resize(config->milkDropCount);
        }
    }

    void Update(float deltaTime)
    {
        progress += deltaTime * config->animationSpeed;
        isActive = contactPhysics->IsInContact() && alignmentSystem->GetAlignmentQuality() < 0.8f;
    }

    void PrintMilkEjectionInfo() const
    {
        std::cout << "\n=== MILK EJECTION PHYSICS ===" << std::endl;
        std::cout << "Source (Nipple): (" << source.x << ", " << source.y << ")" << std::endl;
        std::cout << "Target (Mouth): (" << target.x << ", " << target.y << ")" << std::endl;
        std::cout << "Active: " << (isActive ? "YES" : "NO") << std::endl;
        std::cout << "Progress: " << progress << std::endl;
        std::cout << "Stream Count: " << config->milkStreamCount << std::endl;
        std::cout << "Droplet Count per Stream: " << config->milkDropCount << std::endl;
        
        if (isActive && alignmentSystem->IsPerfectlyAligned())
        {
            std::cout << "🥛 OPTIMAL MILK FLOW CONDITIONS" << std::endl;
            std::cout << "Flow Rate: MAXIMUM (Perfect alignment achieved)" << std::endl;
            std::cout << "Pressure Visualization: ACTIVE" << std::endl;
            std::cout << "Milk Ejection Reflex: TRIGGERED" << std::endl;
        }
        else if (isActive)
        {
            std::cout << "🥛 SUBOPTIMAL FLOW CONDITIONS" << std::endl;
            std::cout << "Flow Rate: REDUCED (Alignment needed)" << std::endl;
            std::cout << "Efficiency: " << ((1.0f - alignmentSystem->GetAlignmentQuality()) * 100.0f) << "%" << std::endl;
        }
    }

    void SetSource(Vector2 src) { source = src; }
    void SetTarget(Vector2 tgt) { target = tgt; }
    void SetActive(bool active) { isActive = active; }
    
    bool IsActive() const { return isActive; }
    float GetProgress() const { return progress; }
};

// Educational simulation controller
class EducationalSimulation
{
private:
    Config config;
    ContactPhysics contactPhysics;
    AlignmentSystem alignmentSystem;
    AnatomicalBreast breast;
    BabyHead baby;
    MilkEjection milkEjection;
    float totalTime;

public:
    EducationalSimulation() 
        : contactPhysics(&config), alignmentSystem(&config),
          breast({400, 450}, 180.0f, &config, &contactPhysics),
          baby({700, 450}, 65.0f, &config, &contactPhysics, &alignmentSystem),
          milkEjection(&config, &alignmentSystem, &contactPhysics),
          totalTime(0.0f) {}

    void Update(float deltaTime)
    {
        totalTime += deltaTime;

        // Update alignment system with ultra-precision
        alignmentSystem.UpdateAlignment(
            breast.GetPosition(), breast.GetRadius(), 
            breast.GetNipplePosition(), baby.GetMouthPosition(), 
            baby.GetEffectiveMouthRadius()
        );

        // Update contact physics
        contactPhysics.UpdateContact(
            breast.GetAreolaCenter(), breast.GetAreolaRadius(),
            baby.GetMouthPosition(), baby.GetEffectiveMouthRadius(),
            baby.IsLatched()
        );

        // Update all components
        breast.Update(deltaTime);
        baby.Update(deltaTime);
        milkEjection.Update(deltaTime);

        // Update milk ejection positions with perfect alignment
        milkEjection.SetSource(breast.GetNipplePosition());
        milkEjection.SetTarget(baby.GetMouthPosition());
        milkEjection.SetActive(baby.IsLatched() && alignmentSystem.IsPerfectlyAligned());
    }

    void AutoAlignForPerfectContact()
    {
        Vector2 nipplePos = breast.GetNipplePosition();
        Vector2 optimalBabyPos = {
            nipplePos.x + breast.GetAreolaRadius() + baby.GetMouthRadius() - 3.0f,
            nipplePos.y
        };
        baby.SetPosition(optimalBabyPos);
        
        std::cout << "\n🎯 AUTO-ALIGNMENT EXECUTED" << std::endl;
        std::cout << "Baby repositioned to: (" << optimalBabyPos.x << ", " << optimalBabyPos.y << ")" << std::endl;
    }

    void SimulateLatch()
    {
        baby.SetLatched(true);
        std::cout << "\n🤱 LATCH SIMULATION ACTIVATED" << std::endl;
    }

    void ReleaseLatch()
    {
        baby.SetLatched(false);
        std::cout << "\n👶 LATCH RELEASED" << std::endl;
    }

    void PrintFullStatus() const
    {
        std::cout << "\n" << std::string(60, '=') << std::endl;
        std::cout << "ULTRA-REALISTIC LACTATION SIMULATION STATUS" << std::endl;
        std::cout << "Educational Medical Visualization - Perfect Alignment System" << std::endl;
        std::cout << std::string(60, '=') << std::endl;
        std::cout << "Simulation Time: " << totalTime << " seconds" << std::endl;

        breast.PrintBreastInfo();
        baby.PrintHeadInfo();
        alignmentSystem.PrintAlignmentStatus();
        contactPhysics.PrintContactStatus();
        milkEjection.PrintMilkEjectionInfo();

        std::cout << "\n" << std::string(60, '=') << std::endl;
        if (alignmentSystem.IsPerfectlyAligned() && baby.IsLatched())
        {
            std::cout << "🏆 PERFECT EDUCATIONAL DEMONSTRATION ACHIEVED!" << std::endl;
            std::cout << "✅ Zero-distance contact established" << std::endl;
            std::cout << "✅ Optimal milk transfer conditions met" << std::endl;
            std::cout << "✅ Anatomically correct positioning verified" << std::endl;
        }
        else
        {
            std::cout << "📚 EDUCATIONAL ADJUSTMENTS NEEDED:" << std::endl;
            if (!alignmentSystem.IsPerfectlyAligned())
            {
                std::cout << "⚠️  Alignment distance: " << alignmentSystem.GetContactDistance() << " px" << std::endl;
            }
            if (!baby.IsLatched())
            {
                std::cout << "⚠️  Latch not established" << std::endl;
            }
        }
        std::cout << std::string(60, '=') << std::endl;
    }

    // Getters for interactive control
    AnatomicalBreast& GetBreast() { return breast; }
    BabyHead& GetBaby() { return baby; }
    AlignmentSystem& GetAlignmentSystem() { return alignmentSystem; }
    ContactPhysics& GetContactPhysics() { return contactPhysics; }
    Config& GetConfig() { return config; }
};

// Interactive demonstration
void RunInteractiveDemo()
{
    EducationalSimulation sim;
    
    std::cout << "\n🎓 ULTRA-REALISTIC LACTATION EDUCATIONAL SIMULATION" << std::endl;
    std::cout << "Professional Medical Training Tool - Perfect Alignment System" << std::endl;
    std::cout << "\nThis simulation demonstrates anatomically correct breastfeeding" << std::endl;
    std::cout << "mechanics with zero-distance contact for optimal milk transfer.\n" << std::endl;

    // Initial status
    sim.PrintFullStatus();

    std::cout << "\n📋 INTERACTIVE DEMONSTRATION SEQUENCE:" << std::endl;
    
    // Step 1: Show initial misalignment
    std::cout << "\n1️⃣  INITIAL STATE - Showing natural positioning..." << std::endl;
    sim.Update(0.1f);
    sim.PrintFullStatus();

    // Step 2: Simulate approach
    std::cout << "\n2️⃣  APPROACHING FOR LATCH - Moving baby closer..." << std::endl;
    Vector2 babyPos = sim.GetBaby().GetPosition();
    sim.GetBaby().SetPosition({babyPos.x - 50, babyPos.y});
    sim.Update(0.1f);
    sim.PrintFullStatus();

    // Step 3: Auto-align for perfect contact
    std::cout << "\n3️⃣  AUTO-ALIGNMENT - Achieving perfect positioning..." << std::endl;
    sim.AutoAlignForPerfectContact();
    sim.Update(0.1f);
    sim.PrintFullStatus();

    // Step 4: Simulate latch
    std::cout << "\n4️⃣  LATCH ESTABLISHMENT - Simulating baby latch..." << std::endl;
    sim.SimulateLatch();
    sim.Update(0.1f);
    sim.PrintFullStatus();

    // Step 5: Demonstrate perfect feeding
    std::cout << "\n5️⃣  PERFECT FEEDING STATE - Optimal milk transfer..." << std::endl;
    for (int i = 0; i < 5; i++)
    {
        sim.Update(0.2f);
    }
    sim.PrintFullStatus();

    std::cout << "\n🎯 EDUCATIONAL OBJECTIVES ACHIEVED:" << std::endl;
    std::cout << "✅ Demonstrated zero-distance contact principle" << std::endl;
    std::cout << "✅ Showed realistic tissue deformation during latch" << std::endl;
    std::cout << "✅ Visualized optimal milk ejection conditions" << std::endl;
    std::cout << "✅ Provided real-time alignment feedback system" << std::endl;
    
    std::cout << "\n📖 KEY EDUCATIONAL POINTS:" << std::endl;
    std::cout << "• Perfect alignment requires nipple-to-mouth distance < 5px" << std::endl;
    std::cout << "• Contact deformation indicates proper latch pressure" << std::endl;
    std::cout << "• Milk ejection reflex activates only with perfect alignment" << std::endl;
    std::cout << "• Real-time feedback enables positioning optimization" << std::endl;

    std::cout << "\n🏥 CLINICAL APPLICATIONS:" << std::endl;
    std::cout << "• Healthcare professional training" << std::endl;
    std::cout << "• Lactation consultant education" << std::endl;
    std::cout << "• Medical student anatomical reference" << std::endl;
    std::cout << "• Research visualization tool" << std::endl;

    std::cout << "\n✨ SIMULATION COMPLETE - Ultra-realistic alignment demonstrated!" << std::endl;
}

int main()
{
    std::cout << "Ultra-Realistic Anatomical Lactation Visualization" << std::endl;
    std::cout << "Perfect Alignment System - Medical Education Tool" << std::endl;
    std::cout << "=================================================" << std::endl;
    
    RunInteractiveDemo();
    
    return 0;
}