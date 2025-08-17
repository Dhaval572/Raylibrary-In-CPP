#include <raylib.h>
#include <rlImGui.h>
#include <imgui.h>
#include <raymath.h>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>

// Forward declarations
class AnatomicalBreast;
class BabyMouth;
class MilkEjection;
class UIController;
class Application;
class TextureManager;
class LightingSystem;
class AlignmentSystem;
class ContactPhysics;

// Advanced utility class for mathematical operations
class MathUtils
{
public:
    static Vector2 CubicBezier(const Vector2 &p0, const Vector2 &p1, const Vector2 &p2, const Vector2 &p3, float t)
    {
        float u = 1.0f - t;
        float uu = u * u;
        float uuu = uu * u;
        float tt = t * t;
        float ttt = tt * t;

        Vector2 p = Vector2Scale(p0, uuu);
        p = Vector2Add(p, Vector2Scale(p1, 3 * uu * t));
        p = Vector2Add(p, Vector2Scale(p2, 3 * u * tt));
        p = Vector2Add(p, Vector2Scale(p3, ttt));

        return p;
    }

    static float Lerp(float a, float b, float t)
    {
        return a + t * (b - a);
    }

    static float SmoothStep(float edge0, float edge1, float x)
    {
        float t = Clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
        return t * t * (3.0f - 2.0f * t);
    }

    static Vector2 PolarToCartesian(Vector2 center, float radius, float angle)
    {
        return {center.x + radius * cosf(angle), center.y + radius * sinf(angle)};
    }

    static float Noise(float x, float y)
    {
        return (sinf(x * 12.9898f + y * 78.233f) * 43758.5453f);
    }

    static float PerlinNoise(float x, float y)
    {
        float noise = 0.0f;
        noise += sinf(x * 0.02f) * cosf(y * 0.03f) * 0.5f;
        noise += sinf(x * 0.05f) * cosf(y * 0.07f) * 0.25f;
        noise += sinf(x * 0.1f) * cosf(y * 0.11f) * 0.125f;
        return noise;
    }

    static Vector2 CalculateContactPoint(Vector2 breastCenter, float breastRadius, Vector2 mouthCenter, float mouthRadius)
    {
        Vector2 direction = Vector2Normalize(Vector2Subtract(mouthCenter, breastCenter));
        return Vector2Add(breastCenter, Vector2Scale(direction, breastRadius));
    }

    static float CalculateContactDistance(Vector2 breastPos, float breastRadius, Vector2 mouthPos, float mouthRadius)
    {
        float centerDistance = Vector2Distance(breastPos, mouthPos);
        return fmaxf(0.0f, centerDistance - (breastRadius + mouthRadius));
    }

    static Vector2 CalculatePerfectAlignmentPosition(Vector2 breastPos, float breastRadius, Vector2 mouthPos, float mouthRadius, float nippleOffset)
    {
        Vector2 nipplePos = {breastPos.x, breastPos.y - nippleOffset};
        Vector2 direction = Vector2Normalize(Vector2Subtract(mouthPos, nipplePos));
        return Vector2Add(nipplePos, Vector2Scale(direction, breastRadius * 0.1f));
    }
};

// Enhanced configuration with ultra-realistic parameters
class Config
{
public:
    static const int SCREEN_WIDTH = 1400;
    static const int SCREEN_HEIGHT = 800;
    static const int TARGET_FPS = 60;

    // Ultra-realistic skin tones and colors
    Color baseSkinColor = {245, 210, 190, 255};
    Color shadowSkinColor = {220, 185, 165, 255};
    Color highlightSkinColor = {255, 235, 215, 255};

    Color areolaBaseColor = {180, 130, 120, 255};
    Color areolaShadowColor = {140, 90, 80, 255};
    Color areolaHighlightColor = {200, 150, 140, 255};

    Color nippleColor = {160, 110, 100, 255};
    Color nippleTipColor = {140, 90, 80, 255};

    Color babySkinColor = {252, 225, 205, 255};
    Color babyBlushColor = {255, 200, 190, 255};

    Color lipColor = {220, 150, 140, 255};
    Color innerLipColor = {245, 180, 170, 255};
    Color tongueColor = {255, 190, 180, 255};
    Color gumsColor = {240, 200, 195, 255};

    Color milkColor = {248, 248, 245, 220};
    Color milkHighlightColor = {255, 255, 252, 180};

    // Contact and alignment colors
    Color alignmentGuideColor = {0, 255, 0, 150};
    Color misalignmentColor = {255, 100, 100, 150};
    Color perfectContactColor = {0, 255, 0, 200};
    Color contactZoneColor = {255, 255, 0, 100};

    // Advanced lighting
    Vector2 lightPosition = {300, 200};
    float ambientStrength = 0.3f;
    float diffuseStrength = 0.7f;
    float specularStrength = 0.4f;

    // Animation settings
    float animationSpeed = 0.8f;
    int milkDropCount = 15;
    int milkStreamCount = 6;

    // Alignment settings
    float perfectAlignmentThreshold = 5.0f;
    float contactDeformationAmount = 0.15f;
    bool showAlignmentGuides = true;
    bool enableAutoAlignment = false;
    float alignmentSensitivity = 2.0f;

    // Texture detail levels
    int skinTextureDetail = 60;
    int areolaTextureDetail = 40;
    float skinBumpiness = 0.4f;
    float veinVisibility = 0.25f;
};

// Advanced alignment system for perfect positioning
class AlignmentSystem
{
private:
    Config *config;
    bool isPerfectlyAligned;
    float alignmentQuality;
    Vector2 idealContactPoint;
    float contactDistance;

public:
    AlignmentSystem(Config *cfg) : config(cfg), isPerfectlyAligned(false), alignmentQuality(0.0f), contactDistance(0.0f) {}

    void UpdateAlignment(Vector2 breastPos, float breastRadius, Vector2 nipplePos, Vector2 mouthPos, float mouthRadius)
    {
        // Calculate contact distance
        contactDistance = MathUtils::CalculateContactDistance(nipplePos, breastRadius * 0.3f, mouthPos, mouthRadius);
        
        // Calculate alignment quality (0.0 = perfect, 1.0 = completely misaligned)
        alignmentQuality = fminf(1.0f, contactDistance / config->perfectAlignmentThreshold);
        
        // Determine if perfectly aligned
        isPerfectlyAligned = contactDistance < config->perfectAlignmentThreshold;
        
        // Calculate ideal contact point
        idealContactPoint = MathUtils::CalculatePerfectAlignmentPosition(breastPos, breastRadius, mouthPos, mouthRadius, breastRadius * 0.15f);
    }

    void DrawAlignmentGuides(Vector2 breastPos, Vector2 nipplePos, Vector2 mouthPos, float mouthRadius) const
    {
        if (!config->showAlignmentGuides) return;

        // Draw alignment line between nipple and mouth center
        Color lineColor = isPerfectlyAligned ? config->perfectContactColor : config->misalignmentColor;
        lineColor.a = 120;
        DrawLineEx(nipplePos, mouthPos, 2.0f, lineColor);

        // Draw contact zone indicator
        Color zoneColor = config->contactZoneColor;
        zoneColor.a = (unsigned char)(100 * (1.0f - alignmentQuality));
        DrawCircleLines(mouthPos.x, mouthPos.y, mouthRadius + config->perfectAlignmentThreshold, zoneColor);

        // Draw perfect alignment indicator
        if (isPerfectlyAligned)
        {
            DrawCircleV(idealContactPoint, 4.0f, config->perfectContactColor);
            DrawText("PERFECT ALIGNMENT", mouthPos.x - 60, mouthPos.y - mouthRadius - 30, 16, config->perfectContactColor);
        }
        else
        {
            // Draw distance indicator
            DrawText(TextFormat("Distance: %.1f px", contactDistance), mouthPos.x - 50, mouthPos.y - mouthRadius - 30, 14, config->misalignmentColor);
        }

        // Draw alignment quality bar
        DrawAlignmentQualityIndicator();
    }

    void DrawAlignmentQualityIndicator() const
    {
        Rectangle qualityBar = {50, 150, 200, 20};
        DrawRectangleRec(qualityBar, {50, 50, 50, 200});
        
        float qualityWidth = qualityBar.width * (1.0f - alignmentQuality);
        Color qualityColor = isPerfectlyAligned ? config->perfectContactColor : 
                           alignmentQuality < 0.5f ? YELLOW : config->misalignmentColor;
        
        Rectangle qualityFill = {qualityBar.x, qualityBar.y, qualityWidth, qualityBar.height};
        DrawRectangleRec(qualityFill, qualityColor);
        
        DrawText("Alignment Quality", 50, 130, 14, DARKGRAY);
        DrawText(isPerfectlyAligned ? "PERFECT" : "ADJUST POSITION", 260, 155, 12, 
                isPerfectlyAligned ? config->perfectContactColor : config->misalignmentColor);
    }

    Vector2 GetAutoAlignmentSuggestion(Vector2 currentMouthPos, Vector2 nipplePos, float mouthRadius) const
    {
        if (!config->enableAutoAlignment) return currentMouthPos;
        
        Vector2 direction = Vector2Normalize(Vector2Subtract(currentMouthPos, nipplePos));
        return Vector2Add(nipplePos, Vector2Scale(direction, mouthRadius * 0.8f));
    }

    bool IsPerfectlyAligned() const { return isPerfectlyAligned; }
    float GetAlignmentQuality() const { return alignmentQuality; }
    float GetContactDistance() const { return contactDistance; }
};

// Contact physics system for realistic deformation
class ContactPhysics
{
private:
    Config *config;
    float deformationAmount;
    Vector2 contactPoint;
    bool isInContact;
    std::vector<Vector2> deformationPoints;

public:
    ContactPhysics(Config *cfg) : config(cfg), deformationAmount(0.0f), isInContact(false) {}

    void UpdateContact(Vector2 breastPos, float breastRadius, Vector2 mouthPos, float mouthRadius, bool isLatched)
    {
        float distance = Vector2Distance(breastPos, mouthPos);
        isInContact = distance < (breastRadius + mouthRadius) && isLatched;
        
        if (isInContact)
        {
            // Calculate deformation based on contact pressure
            float overlap = (breastRadius + mouthRadius) - distance;
            deformationAmount = fminf(config->contactDeformationAmount, overlap * 0.1f);
            
            // Calculate contact point
            Vector2 direction = Vector2Normalize(Vector2Subtract(mouthPos, breastPos));
            contactPoint = Vector2Add(breastPos, Vector2Scale(direction, breastRadius - deformationAmount));
            
            // Generate deformation points around contact area
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
            float angle = (float)i / (numPoints - 1) * PI * 2.0f;
            float deformRadius = deformationAmount * 15.0f;
            Vector2 deformPoint = {
                contactPoint.x + deformRadius * cosf(angle),
                contactPoint.y + deformRadius * sinf(angle)
            };
            deformationPoints.push_back(deformPoint);
        }
    }

    void DrawContactDeformation() const
    {
        if (!isInContact || deformationPoints.empty()) return;

        // Draw deformation visualization
        Color deformColor = config->contactZoneColor;
        deformColor.a = 150;
        
        for (size_t i = 0; i < deformationPoints.size(); i++)
        {
            size_t next = (i + 1) % deformationPoints.size();
            DrawLineEx(deformationPoints[i], deformationPoints[next], 2.0f, deformColor);
        }

        // Draw contact pressure indicator
        DrawCircleV(contactPoint, 3.0f, config->perfectContactColor);
    }

    float GetDeformationAmount() const { return deformationAmount; }
    bool IsInContact() const { return isInContact; }
    Vector2 GetContactPoint() const { return contactPoint; }
};

// Advanced lighting system
class LightingSystem
{
private:
    Config *config;

public:
    LightingSystem(Config *cfg) : config(cfg) {}

    Color CalculateLighting(Vector2 position, Vector2 normal, Color baseColor) const
    {
        Vector2 lightDir = Vector2Normalize(Vector2Subtract(config->lightPosition, position));
        float lightDistance = Vector2Distance(config->lightPosition, position);

        // Normalize normal vector
        normal = Vector2Normalize(normal);

        // Calculate lighting components
        float ambient = config->ambientStrength;
        float diffuse = fmaxf(0.0f, Vector2DotProduct(normal, lightDir)) * config->diffuseStrength;
        float attenuation = 1.0f / (1.0f + 0.001f * lightDistance);

        float totalLight = (ambient + diffuse * attenuation);
        totalLight = Clamp(totalLight, 0.2f, 1.2f);

        return ColorBrightness(baseColor, totalLight - 1.0f);
    }

    Color CalculateShadow(Vector2 position, float shadowIntensity, Color baseColor) const
    {
        return ColorBrightness(baseColor, -shadowIntensity);
    }
};

// Enhanced anatomical breast with ultra-realistic details and contact physics
class AnatomicalBreast
{
private:
    Vector2 position;
    float radius;
    Config *config;
    LightingSystem *lighting;
    ContactPhysics *contactPhysics;
    float breathingPhase;
    std::vector<Vector2> skinPores;
    std::vector<Vector2> veinPoints;

    void GenerateSkinDetails()
    {
        skinPores.clear();
        veinPoints.clear();

        // Generate skin pores with more realistic distribution
        for (int i = 0; i < config->skinTextureDetail; i++)
        {
            float angle = (float)i / config->skinTextureDetail * PI * 2.0f;
            float r = radius * (0.7f + 0.3f * ((float)rand() / RAND_MAX));
            Vector2 pore = {
                position.x + r * cosf(angle) + (((float)rand() / RAND_MAX) - 0.5f) * 20.0f,
                position.y + r * sinf(angle) * 0.8f + (((float)rand() / RAND_MAX) - 0.5f) * 20.0f};
            skinPores.push_back(pore);
        }

        // Generate more realistic vein patterns
        for (int i = 0; i < 20; i++)
        {
            float angle = (float)i / 20.0f * PI * 2.0f;
            float r = radius * (0.4f + 0.4f * ((float)rand() / RAND_MAX));
            Vector2 vein = {
                position.x + r * cosf(angle),
                position.y + r * sinf(angle) * 0.7f};
            veinPoints.push_back(vein);
        }
    }

    void DrawAdvancedBreastMound() const
    {
        // Account for contact deformation
        float currentRadius = radius;
        Vector2 currentPosition = position;
        
        if (contactPhysics->IsInContact())
        {
            currentRadius -= contactPhysics->GetDeformationAmount() * radius * 0.1f;
        }

        // Multiple layers for ultra-realistic depth
        std::vector<Vector2> outerPoints(32);
        std::vector<Vector2> innerPoints(28);

        // Outer contour with enhanced natural asymmetry
        for (int i = 0; i < 32; i++)
        {
            float angle = (float)i / 31.0f * PI * 1.9f - PI * 0.45f;
            float noise = MathUtils::PerlinNoise(currentPosition.x + angle * 100, currentPosition.y) * 0.05f;
            float r = currentRadius * (0.95f + 0.1f * cosf(angle * 2.0f) + noise);
            float breathing = sinf(breathingPhase) * 2.0f;

            outerPoints[i] = {
                currentPosition.x + (r + breathing) * cosf(angle),
                currentPosition.y - (r + breathing) * sinf(angle) * 0.75f};
        }

        // Inner shading layer
        for (int i = 0; i < 28; i++)
        {
            float angle = (float)i / 27.0f * PI * 1.7f - PI * 0.35f;
            float r = currentRadius * 0.85f;
            innerPoints[i] = {
                currentPosition.x + r * cosf(angle),
                currentPosition.y - r * sinf(angle) * 0.7f};
        }

        // Draw base with enhanced gradient effect
        Vector2 center = currentPosition;
        Vector2 normal = {0, -1};
        Color baseColor = lighting->CalculateLighting(center, normal, config->baseSkinColor);
        DrawTriangleFan(outerPoints.data(), 32, baseColor);

        // Draw inner shadow for enhanced depth
        Color shadowColor = lighting->CalculateShadow(center, 0.15f, config->shadowSkinColor);
        DrawTriangleFan(innerPoints.data(), 28, shadowColor);

        // Draw enhanced skin texture
        DrawSkinTexture();

        // Draw more visible veins
        if (config->veinVisibility > 0.1f)
        {
            DrawSubtleVeins();
        }

        // Draw contact deformation
        contactPhysics->DrawContactDeformation();
    }

    void DrawSkinTexture() const
    {
        for (const Vector2 &pore : skinPores)
        {
            float dist = Vector2Distance(pore, position);
            if (dist < radius * 0.9f)
            {
                Color poreColor = ColorBrightness(config->baseSkinColor, -0.12f);
                poreColor.a = 120;
                DrawCircleV(pore, 1.0f, poreColor);
            }
        }
    }

    void DrawSubtleVeins() const
    {
        for (size_t i = 0; i < veinPoints.size() - 1; i++)
        {
            Color veinColor = ColorBrightness(config->baseSkinColor, -0.25f);
            veinColor.a = (unsigned char)(config->veinVisibility * 140);
            DrawLineEx(veinPoints[i], veinPoints[i + 1], 2.0f, veinColor);
        }
    }

    void DrawRealisticAreola() const
    {
        float areolaRadius = radius * 0.35f;
        Vector2 areolaCenter = {position.x, position.y - radius * 0.05f};

        // Account for contact deformation
        if (contactPhysics->IsInContact())
        {
            areolaRadius *= (1.0f - contactPhysics->GetDeformationAmount() * 0.5f);
        }

        // Multiple layers for ultra-realistic areola
        for (int layer = 0; layer < 4; layer++)
        {
            float layerRadius = areolaRadius * (1.0f - layer * 0.08f);
            Color layerColor;

            switch (layer)
            {
            case 0:
                layerColor = config->areolaBaseColor;
                break;
            case 1:
                layerColor = ColorBrightness(config->areolaBaseColor, 0.1f);
                break;
            case 2:
                layerColor = ColorBrightness(config->areolaBaseColor, 0.2f);
                break;
            case 3:
                layerColor = ColorBrightness(config->areolaBaseColor, 0.35f);
                break;
            }

            // Draw with enhanced bumpy texture
            for (int i = 0; i < 64; i++)
            {
                float angle = (float)i / 63.0f * PI * 2.0f;
                float noise = MathUtils::PerlinNoise(areolaCenter.x + angle * 50, areolaCenter.y) * 0.12f;
                float r = layerRadius * (0.94f + 0.12f * cosf(angle * 8.0f) + noise);

                Vector2 pos = {
                    areolaCenter.x + r * cosf(angle),
                    areolaCenter.y + r * sinf(angle) * 0.85f};

                Vector2 normal = Vector2Normalize(Vector2Subtract(pos, areolaCenter));
                Color litColor = lighting->CalculateLighting(pos, normal, layerColor);

                DrawCircleV(pos, layerRadius * 0.06f, litColor);
            }
        }

        // Draw Montgomery glands with enhanced detail
        DrawMontgomeryGlands(areolaCenter, areolaRadius);
    }

    void DrawMontgomeryGlands(Vector2 areolaCenter, float areolaRadius) const
    {
        for (int i = 0; i < 18; i++)
        {
            float angle = (float)i / 17.0f * PI * 2.0f;
            float r = areolaRadius * (0.6f + 0.25f * ((float)rand() / RAND_MAX));
            Vector2 glandPos = {
                areolaCenter.x + r * cosf(angle),
                areolaCenter.y + r * sinf(angle) * 0.8f};

            float glandSize = areolaRadius * (0.05f + 0.04f * ((float)rand() / RAND_MAX));
            Color glandColor = ColorBrightness(config->areolaHighlightColor, 0.25f);

            // Draw gland with enhanced highlight
            DrawCircleV(glandPos, glandSize, glandColor);

            Vector2 highlightPos = {glandPos.x - glandSize * 0.3f, glandPos.y - glandSize * 0.3f};
            DrawCircleV(highlightPos, glandSize * 0.5f, config->highlightSkinColor);
        }
    }

    void DrawRealisticNipple() const
    {
        float areolaRadius = radius * 0.35f;
        float nippleRadius = areolaRadius * 0.42f;
        Vector2 nipplePos = {position.x, position.y - areolaRadius * 0.12f};

        // Account for contact deformation
        if (contactPhysics->IsInContact())
        {
            nippleRadius *= (1.0f - contactPhysics->GetDeformationAmount() * 0.3f);
            nipplePos.y += contactPhysics->GetDeformationAmount() * 5.0f;
        }

        // Enhanced nipple base - more protruding
        Color nippleBaseColor = lighting->CalculateLighting(nipplePos, {0, -1}, config->nippleColor);
        DrawCircleV(nipplePos, nippleRadius, nippleBaseColor);

        // Enhanced nipple tip with more anatomical detail
        Vector2 tipPos = {nipplePos.x, nipplePos.y - nippleRadius * 0.25f};
        Color nippleTipColor = lighting->CalculateLighting(tipPos, {0, -1}, config->nippleTipColor);
        DrawCircleV(tipPos, nippleRadius * 0.75f, nippleTipColor);

        // More detailed nipple opening (for milk ejection)
        DrawCircleV(tipPos, nippleRadius * 0.25f, ColorBrightness(config->nippleTipColor, -0.5f));

        // Enhanced nipple texture with more detail
        for (int i = 0; i < 12; i++)
        {
            float angle = (float)i / 11.0f * PI * 2.0f;
            Vector2 texturePos = {
                tipPos.x + nippleRadius * 0.45f * cosf(angle),
                tipPos.y + nippleRadius * 0.45f * sinf(angle)};
            Color textureColor = ColorBrightness(config->nippleTipColor, -0.15f);
            textureColor.a = 170;
            DrawCircleV(texturePos, 0.7f, textureColor);
        }

        // Enhanced highlight for more realistic roundness
        Vector2 highlightPos = {nipplePos.x - nippleRadius * 0.35f, nipplePos.y - nippleRadius * 0.45f};
        Color highlight = config->highlightSkinColor;
        highlight.a = 200;
        DrawCircleV(highlightPos, nippleRadius * 0.35f, highlight);
    }

public:
    AnatomicalBreast(Vector2 pos, float rad, Config *cfg, LightingSystem *light, ContactPhysics *contact)
        : position(pos), radius(rad), config(cfg), lighting(light), contactPhysics(contact), breathingPhase(0.0f)
    {
        GenerateSkinDetails();
    }

    void Update(float deltaTime)
    {
        breathingPhase += deltaTime * 0.6f; // Enhanced breathing animation
    }

    void Draw() const
    {
        DrawAdvancedBreastMound();
        DrawRealisticAreola();
        DrawRealisticNipple();
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
    Config *config;
    LightingSystem *lighting;
    ContactPhysics *contactPhysics;
    float suckingPhase;
    float jawOpenness;
    Vector2 alignmentTarget;

    void DrawRealisticLips() const
    {
        // Account for jaw openness and alignment
        float currentRadius = radius * (1.0f + jawOpenness * 0.3f);
        
        // Upper lip with enhanced realism
        Vector2 upperLipCenter = {position.x, position.y - currentRadius * 0.35f};
        Color upperLipColor = lighting->CalculateLighting(upperLipCenter, {0, -1}, config->lipColor);

        // Draw upper lip with natural curve and alignment adaptation
        std::vector<Vector2> upperLipPoints(16);
        for (int i = 0; i < 16; i++)
        {
            float t = (float)i / 15.0f;
            float angle = PI * (0.15f + 0.7f * t);
            float r = currentRadius * (0.85f + 0.15f * sinf(t * PI * 4));
            
            // Add alignment deformation
            if (isLatched && contactPhysics->IsInContact())
            {
                r *= (1.0f + contactPhysics->GetDeformationAmount() * 0.4f);
            }
            
            upperLipPoints[i] = {
                upperLipCenter.x + r * cosf(angle),
                upperLipCenter.y - r * sinf(angle) * 0.25f};
        }
        DrawTriangleFan(upperLipPoints.data(), 16, upperLipColor);

        // Lower lip with enhanced detail
        Vector2 lowerLipCenter = {position.x, position.y + currentRadius * 0.35f};
        Color lowerLipColor = lighting->CalculateLighting(lowerLipCenter, {0, 1}, config->lipColor);

        std::vector<Vector2> lowerLipPoints(16);
        for (int i = 0; i < 16; i++)
        {
            float t = (float)i / 15.0f;
            float angle = PI * (1.15f + 0.7f * t);
            float r = currentRadius * (0.85f + 0.15f * sinf(t * PI * 4));
            
            // Add alignment deformation
            if (isLatched && contactPhysics->IsInContact())
            {
                r *= (1.0f + contactPhysics->GetDeformationAmount() * 0.4f);
            }
            
            lowerLipPoints[i] = {
                lowerLipCenter.x + r * cosf(angle),
                lowerLipCenter.y - r * sinf(angle) * 0.25f};
        }
        DrawTriangleFan(lowerLipPoints.data(), 16, lowerLipColor);

        // Enhanced lip highlights with contact adaptation
        Vector2 upperHighlight = {upperLipCenter.x - currentRadius * 0.25f, upperLipCenter.y - currentRadius * 0.15f};
        Vector2 lowerHighlight = {lowerLipCenter.x - currentRadius * 0.35f, lowerLipCenter.y + currentRadius * 0.15f};

        Color highlight = config->highlightSkinColor;
        highlight.a = isLatched ? 200 : 160;
        DrawCircleV(upperHighlight, currentRadius * 0.18f, highlight);
        DrawCircleV(lowerHighlight, currentRadius * 0.22f, highlight);

        // Draw lip seal when latched
        if (isLatched && contactPhysics->IsInContact())
        {
            DrawLipSeal(upperLipCenter, lowerLipCenter, currentRadius);
        }
    }

    void DrawLipSeal(Vector2 upperLip, Vector2 lowerLip, float currentRadius) const
    {
        // Draw realistic lip seal around contact area
        Color sealColor = ColorBrightness(config->lipColor, 0.1f);
        sealColor.a = 180;
        
        Vector2 sealCenter = {(upperLip.x + lowerLip.x) * 0.5f, (upperLip.y + lowerLip.y) * 0.5f};
        float sealRadius = currentRadius * 0.8f;
        
        // Draw seal with contact deformation
        for (int i = 0; i < 24; i++)
        {
            float angle = (float)i / 23.0f * PI * 2.0f;
            float r = sealRadius * (0.9f + 0.1f * cosf(angle * 6.0f));
            Vector2 sealPoint = {
                sealCenter.x + r * cosf(angle),
                sealCenter.y + r * sinf(angle) * 0.6f};
            DrawCircleV(sealPoint, 1.5f, sealColor);
        }
    }

    void DrawRealisticTongue() const
    {
        if (isLatched)
        {
            Vector2 tonguePos = {position.x, position.y + radius * 0.05f};
            float tongueWidth = radius * 0.8f;
            float tongueHeight = radius * 0.5f;

            // Account for sucking motion
            float suckingMotion = sinf(suckingPhase * 8.0f) * 0.1f;
            tongueWidth *= (1.0f + suckingMotion);
            tongueHeight *= (1.0f - suckingMotion * 0.5f);

            // Enhanced tongue base with realistic curvature
            Color tongueColor = lighting->CalculateLighting(tonguePos, {0, 0}, config->tongueColor);
            DrawEllipse(tonguePos.x, tonguePos.y, tongueWidth, tongueHeight, tongueColor);

            // Tongue tip with enhanced detail
            Vector2 tongueTip = {tonguePos.x, tonguePos.y - tongueHeight * 0.6f};
            DrawCircleV(tongueTip, tongueWidth * 0.3f, ColorBrightness(tongueColor, 0.1f));

            // Enhanced tongue texture (papillae)
            for (int i = 0; i < 30; i++)
            {
                Vector2 papillaPos = {
                    tonguePos.x + (((float)rand() / RAND_MAX) - 0.5f) * tongueWidth * 0.8f,
                    tonguePos.y + (((float)rand() / RAND_MAX) - 0.5f) * tongueHeight * 0.8f};
                Color papillaColor = ColorBrightness(config->tongueColor, 0.15f);
                papillaColor.a = 140;
                DrawCircleV(papillaPos, 1.0f, papillaColor);
            }

            // Enhanced median sulcus (tongue groove)
            DrawLineEx(
                {tonguePos.x, tonguePos.y - tongueHeight * 0.4f},
                {tonguePos.x, tonguePos.y + tongueHeight * 0.4f},
                2.0f, ColorBrightness(config->tongueColor, -0.25f));

            // Tongue movement visualization during sucking
            if (contactPhysics->IsInContact())
            {
                DrawTongueMovement(tonguePos, tongueWidth, tongueHeight);
            }
        }
    }

    void DrawTongueMovement(Vector2 tonguePos, float width, float height) const
    {
        // Visualize peristaltic tongue movement
        Color movementColor = {255, 255, 255, 60};
        float waveOffset = sinf(suckingPhase * 6.0f) * width * 0.2f;
        
        for (int i = 0; i < 5; i++)
        {
            float y = tonguePos.y - height * 0.3f + (i * height * 0.15f);
            float x = tonguePos.x + waveOffset * sinf(i * 0.5f);
            DrawCircleV({x, y}, width * 0.1f, movementColor);
        }
    }

    void DrawMouthInterior() const
    {
        // Enhanced gums with realistic coloring
        Color gumsColor = lighting->CalculateLighting(position, {0, 0}, config->gumsColor);
        float currentRadius = radius * (1.0f + jawOpenness * 0.2f);
        DrawCircleV(position, currentRadius * 0.9f, gumsColor);

        // Mouth cavity with depth
        float openingSize = currentRadius * (isLatched ? 0.5f : 0.75f);
        if (isLatched)
        {
            // Add sucking motion effect
            openingSize *= (1.0f + 0.15f * sinf(suckingPhase * 8.0f));
        }

        // Draw cavity with gradient for depth
        DrawCircleV(position, openingSize, BLACK);
        
        // Inner cavity highlights for moisture
        Color moistureColor = {255, 255, 255, isLatched ? 120 : 80};
        DrawCircleV({position.x - openingSize * 0.3f, position.y - openingSize * 0.2f},
                    openingSize * 0.25f, moistureColor);

        // Saliva effects during latching
        if (isLatched && contactPhysics->IsInContact())
        {
            DrawSalivaEffects(openingSize);
        }
    }

    void DrawSalivaEffects(float openingSize) const
    {
        // Draw realistic saliva during feeding
        Color salivaColor = {255, 255, 255, 100};
        for (int i = 0; i < 8; i++)
        {
            float angle = (float)i / 7.0f * PI * 2.0f;
            float r = openingSize * (0.6f + 0.2f * sinf(suckingPhase * 4.0f + i));
            Vector2 salivaPos = {
                position.x + r * cosf(angle),
                position.y + r * sinf(angle)};
            DrawCircleV(salivaPos, 1.0f + 0.5f * sinf(suckingPhase * 6.0f + i), salivaColor);
        }
    }

public:
    BabyMouth(Vector2 pos, float rad, Config *cfg, LightingSystem *light, ContactPhysics *contact)
        : position(pos), radius(rad), isLatched(false), config(cfg), lighting(light), 
          contactPhysics(contact), suckingPhase(0.0f), jawOpenness(0.0f) {}

    void Update(float deltaTime)
    {
        suckingPhase += deltaTime * 2.5f;
        
        // Update jaw openness based on latch state
        float targetOpenness = isLatched ? 0.8f : 0.3f;
        jawOpenness = MathUtils::Lerp(jawOpenness, targetOpenness, deltaTime * 8.0f);
    }

    void Draw() const
    {
        DrawMouthInterior();
        DrawRealisticTongue();
        DrawRealisticLips();
    }

    void SetPosition(Vector2 pos) { position = pos; }
    void SetRadius(float rad) { radius = rad; }
    void SetLatched(bool latched) { isLatched = latched; }
    void SetAlignmentTarget(Vector2 target) { alignmentTarget = target; }
    
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
    Config *config;
    LightingSystem *lighting;
    ContactPhysics *contactPhysics;
    AlignmentSystem *alignmentSystem;

    void DrawFacialFeatures() const
    {
        Vector2 headPos = mouth.GetPosition();
        float headRadius = mouth.GetRadius() * 1.8f;

        // Enhanced eyes (closed during feeding)
        Vector2 leftEye = {headPos.x - headRadius * 0.32f, headPos.y - headRadius * 0.45f};
        Vector2 rightEye = {headPos.x + headRadius * 0.32f, headPos.y - headRadius * 0.45f};

        Color eyeColor = ColorBrightness(config->babySkinColor, -0.08f);
        DrawEllipse(leftEye.x, leftEye.y, headRadius * 0.18f, headRadius * 0.09f, eyeColor);
        DrawEllipse(rightEye.x, rightEye.y, headRadius * 0.18f, headRadius * 0.09f, eyeColor);

        // Enhanced eyelashes with more detail
        Color lashColor = {80, 60, 50, 220};
        for (int i = 0; i < 7; i++)
        {
            float offset = (i - 3) * headRadius * 0.025f;
            DrawLineEx({leftEye.x + offset, leftEye.y - headRadius * 0.06f},
                       {leftEye.x + offset, leftEye.y - headRadius * 0.09f}, 1.0f, lashColor);
            DrawLineEx({rightEye.x + offset, rightEye.y - headRadius * 0.06f},
                       {rightEye.x + offset, rightEye.y - headRadius * 0.09f}, 1.0f, lashColor);
        }

        // Enhanced nose with more realistic shape
        Vector2 nosePos = {headPos.x, headPos.y - headRadius * 0.12f};
        Color noseColor = ColorBrightness(config->babySkinColor, -0.04f);
        DrawCircleV(nosePos, headRadius * 0.07f, noseColor);
        
        // Nostrils
        DrawCircleV({nosePos.x - headRadius * 0.03f, nosePos.y + headRadius * 0.02f}, 
                    headRadius * 0.015f, ColorBrightness(noseColor, -0.3f));
        DrawCircleV({nosePos.x + headRadius * 0.03f, nosePos.y + headRadius * 0.02f}, 
                    headRadius * 0.015f, ColorBrightness(noseColor, -0.3f));

        // Enhanced cheeks with feeding blush
        Vector2 leftCheek = {headPos.x - headRadius * 0.42f, headPos.y + headRadius * 0.08f};
        Vector2 rightCheek = {headPos.x + headRadius * 0.42f, headPos.y + headRadius * 0.08f};

        Color blushColor = config->babyBlushColor;
        blushColor.a = mouth.IsLatched() ? 150 : 100;
        DrawCircleV(leftCheek, headRadius * 0.25f, blushColor);
        DrawCircleV(rightCheek, headRadius * 0.25f, blushColor);

        // Dimples when feeding
        if (mouth.IsLatched() && contactPhysics->IsInContact())
        {
            Color dimpleColor = ColorBrightness(config->babySkinColor, -0.1f);
            dimpleColor.a = 120;
            DrawCircleV({leftCheek.x + headRadius * 0.15f, leftCheek.y}, headRadius * 0.08f, dimpleColor);
            DrawCircleV({rightCheek.x - headRadius * 0.15f, rightCheek.y}, headRadius * 0.08f, dimpleColor);
        }
    }

    void DrawHeadContour() const
    {
        Vector2 headPos = mouth.GetPosition();
        float headRadius = mouth.GetRadius() * 1.8f;

        // Enhanced head shape with realistic proportions
        std::vector<Vector2> headPoints(24);
        for (int i = 0; i < 24; i++)
        {
            float angle = (float)i / 23.0f * PI * 2.0f;
            float r = headRadius;
            
            // Make head more oval and realistic
            if (angle > PI * 0.2f && angle < PI * 0.8f) // Top of head
            {
                r *= 1.1f;
            }
            else if (angle > PI * 1.2f && angle < PI * 1.8f) // Bottom/jaw area
            {
                r *= 0.85f;
            }
            
            headPoints[i] = {
                headPos.x + r * cosf(angle),
                headPos.y + r * sinf(angle) * 0.9f};
        }

        // Draw head with enhanced lighting
        Color headColor = lighting->CalculateLighting(headPos, {-0.2f, -0.8f}, config->babySkinColor);
        DrawTriangleFan(headPoints.data(), 24, headColor);

        // Enhanced head highlight
        Vector2 highlightPos = {headPos.x - headRadius * 0.35f, headPos.y - headRadius * 0.4f};
        Color highlight = config->highlightSkinColor;
        highlight.a = 180;
        DrawCircleV(highlightPos, headRadius * 0.5f, highlight);
    }

public:
    BabyHead(Vector2 pos, float mouthRadius, Config *cfg, LightingSystem *light, 
             ContactPhysics *contact, AlignmentSystem *alignment)
        : mouth(pos, mouthRadius, cfg, light, contact), config(cfg), lighting(light), 
          contactPhysics(contact), alignmentSystem(alignment) {}

    void Update(float deltaTime)
    {
        mouth.Update(deltaTime);
    }

    void Draw() const
    {
        DrawHeadContour();
        DrawFacialFeatures();
        mouth.Draw();
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

// Ultra-realistic milk ejection with perfect physics and alignment
class MilkEjection
{
private:
    Vector2 source;
    Vector2 target;
    float progress;
    Config *config;
    AlignmentSystem *alignmentSystem;
    ContactPhysics *contactPhysics;
    std::vector<std::vector<Vector2>> milkDroplets;
    bool isActive;

    void InitializeMilkStreams()
    {
        milkDroplets.resize(config->milkStreamCount);
        for (int stream = 0; stream < config->milkStreamCount; stream++)
        {
            milkDroplets[stream].resize(config->milkDropCount);
        }
    }

    void DrawRealisticMilkStream(int streamIndex) const
    {
        if (!isActive || !contactPhysics->IsInContact()) return;

        // Enhanced stream positioning based on contact alignment
        Vector2 contactPoint = contactPhysics->GetContactPoint();
        float alignmentQuality = alignmentSystem->GetAlignmentQuality();
        
        Vector2 offset = {
            6.0f * (streamIndex - config->milkStreamCount / 2.0f) * (1.0f - alignmentQuality),
            3.0f * (streamIndex - config->milkStreamCount / 2.0f) * (1.0f - alignmentQuality)};

        Vector2 p0 = Vector2Add(source, offset);
        Vector2 p3 = Vector2Add(target, offset);

        // Enhanced curve calculation for perfect alignment
        Vector2 p1 = {
            p0.x + (p3.x - p0.x) * 0.2f,
            p0.y + (p3.y - p0.y) * 0.2f - (20.0f - streamIndex * 2.0f) * alignmentQuality};
        Vector2 p2 = {
            p0.x + (p3.x - p0.x) * 0.8f,
            p0.y + (p3.y - p0.y) * 0.8f - (10.0f - streamIndex * 1.5f) * alignmentQuality};

        // Draw enhanced milk droplets with perfect alignment physics
        for (int d = 0; d < config->milkDropCount; d++)
        {
            float t = fmodf(progress * 2.5f + (float)d / config->milkDropCount + streamIndex * 0.08f, 1.0f);
            Vector2 pos = MathUtils::CubicBezier(p0, p1, p2, p3, t);

            // Enhanced gravity and alignment effects
            float gravity = t * t * 12.0f * (2.0f - alignmentQuality);
            pos.y += gravity;

            // Droplet size varies with alignment quality
            float baseSize = 2.0f + 2.0f * sinf(t * PI * 8.0f) * alignmentQuality;
            float streamVariation = 0.7f + 0.6f * (streamIndex % 3);
            float alignmentBonus = 1.0f + (1.0f - alignmentQuality) * 0.5f;
            float size = baseSize * streamVariation * alignmentBonus;

            // Enhanced milk droplet with perfect alignment coloring
            Color milkColor = config->milkColor;
            if (alignmentSystem->IsPerfectlyAligned())
            {
                milkColor = ColorBrightness(milkColor, 0.2f);
            }
            milkColor.a = (unsigned char)(255 * (1.0f - t * 0.25f));
            DrawCircleV(pos, size, milkColor);

            // Enhanced milk highlight with alignment feedback
            Vector2 highlightPos = {pos.x - size * 0.4f, pos.y - size * 0.4f};
            Color highlightColor = config->milkHighlightColor;
            if (alignmentSystem->IsPerfectlyAligned())
            {
                highlightColor = ColorBrightness(highlightColor, 0.3f);
            }
            highlightColor.a = (unsigned char)(200 * (1.0f - t * 0.15f));
            DrawCircleV(highlightPos, size * 0.7f, highlightColor);

            // Enhanced stream continuity with alignment-based thickness
            if (d > 0)
            {
                float prevT = fmodf(progress * 2.5f + (float)(d - 1) / config->milkDropCount + streamIndex * 0.08f, 1.0f);
                Vector2 prevPos = MathUtils::CubicBezier(p0, p1, p2, p3, prevT);
                prevPos.y += prevT * prevT * 12.0f * (2.0f - alignmentQuality);

                Color streamColor = config->milkColor;
                streamColor.a = (unsigned char)(120 * alignmentQuality);
                float streamThickness = 1.0f + alignmentQuality * 1.5f;
                DrawLineEx(prevPos, pos, streamThickness, streamColor);
            }
        }

        // Draw milk ejection pressure visualization
        if (alignmentSystem->IsPerfectlyAligned())
        {
            DrawMilkPressureVisualization(p0, streamIndex);
        }
    }

    void DrawMilkPressureVisualization(Vector2 nipplePos, int streamIndex) const
    {
        // Visualize milk ejection reflex pressure
        Color pressureColor = {255, 255, 255, 80};
        float pressureRadius = 8.0f + 4.0f * sinf(progress * 10.0f + streamIndex);
        DrawCircleLinesV(nipplePos, pressureRadius, pressureColor);
        
        // Pressure waves
        for (int i = 0; i < 3; i++)
        {
            float waveRadius = pressureRadius + (i * 6.0f) + sinf(progress * 8.0f) * 3.0f;
            Color waveColor = pressureColor;
            waveColor.a = 40 - (i * 10);
            DrawCircleLinesV(nipplePos, waveRadius, waveColor);
        }
    }

public:
    MilkEjection(Config *cfg, AlignmentSystem *alignment, ContactPhysics *contact) 
        : source({0, 0}), target({0, 0}), progress(0.0f), config(cfg), 
          alignmentSystem(alignment), contactPhysics(contact), isActive(false)
    {
        InitializeMilkStreams();
    }

    void Draw() const
    {
        for (int i = 0; i < config->milkStreamCount; i++)
        {
            DrawRealisticMilkStream(i);
        }
    }

    void Update(float deltaTime)
    {
        progress += deltaTime * config->animationSpeed;
        isActive = contactPhysics->IsInContact() && alignmentSystem->GetAlignmentQuality() < 0.8f;
    }

    void SetSource(Vector2 src) { source = src; }
    void SetTarget(Vector2 tgt) { target = tgt; }
    void ResetProgress() { progress = 0.0f; }
    void SetActive(bool active) { isActive = active; }
};

// Enhanced label system with alignment feedback
class LabelSystem
{
private:
    bool showLabels;
    int fontSize;
    int smallFontSize;
    Color textColor;
    Color highlightColor;
    AlignmentSystem *alignmentSystem;

public:
    LabelSystem(AlignmentSystem *alignment) : showLabels(true), fontSize(18), smallFontSize(14),
                    textColor(DARKGRAY), highlightColor({100, 50, 50, 200}), alignmentSystem(alignment) {}

    void DrawBreastLabels(const AnatomicalBreast &breast) const
    {
        if (!showLabels) return;

        Vector2 pos = breast.GetPosition();
        Vector2 nipplePos = breast.GetNipplePosition();
        Vector2 areolaCenter = breast.GetAreolaCenter();
        float radius = breast.GetRadius();

        // Enhanced labels with alignment-based coloring
        Color labelColor = alignmentSystem->IsPerfectlyAligned() ? 
                          Color{0, 150, 0, 255} : textColor;

        DrawLabelWithLeader("Areola Complex", {pos.x - 60, pos.y - radius * 0.5f},
                            areolaCenter, labelColor);
        DrawLabelWithLeader("Nipple-Areolar Junction", {pos.x - 45, pos.y + 25},
                            nipplePos, labelColor);
        DrawLabelWithLeader("Lactiferous Ducts", {pos.x + radius * 0.7f, pos.y - radius * 0.4f},
                            {pos.x + radius * 0.25f, pos.y - radius * 0.15f}, labelColor);
        DrawLabelWithLeader("Montgomery's Glands", {pos.x + radius * 0.8f, pos.y + radius * 0.15f},
                            {pos.x + radius * 0.3f, pos.y + radius * 0.1f}, labelColor);
        
        // Perfect alignment indicator
        if (alignmentSystem->IsPerfectlyAligned())
        {
            DrawText("✓ OPTIMAL LATCH ACHIEVED", pos.x - 80, pos.y - radius - 50, 16, 
                    Color{0, 200, 0, 255});
        }
    }

    void DrawBabyLabels(const BabyHead &baby) const
    {
        if (!showLabels) return;

        Vector2 pos = baby.GetMouthPosition();
        float mouthRadius = baby.GetMouthRadius();

        // Enhanced labels with latch state feedback
        Color labelColor = baby.IsLatched() ? Color{0, 100, 200, 255} : textColor;

        DrawLabelWithLeader("Oral Vestibule", {pos.x - 85, pos.y - mouthRadius * 2.5f},
                            {pos.x, pos.y - mouthRadius * 0.6f}, labelColor);
        DrawLabelWithLeader("Tongue (Peristaltic Motion)", {pos.x - 55, pos.y + mouthRadius * 1.4f},
                            {pos.x, pos.y + mouthRadius * 0.4f}, labelColor);
        DrawLabelWithLeader("Upper Labial Frenulum", {pos.x + 65, pos.y - mouthRadius * 1.8f},
                            {pos.x, pos.y - mouthRadius * 0.4f}, labelColor);
        DrawLabelWithLeader("Lower Lip Seal", {pos.x + 65, pos.y + mouthRadius * 2.0f},
                            {pos.x, pos.y + mouthRadius * 0.4f}, labelColor);

        // Latch quality indicator
        if (baby.IsLatched())
        {
            const char* latchQuality = alignmentSystem->IsPerfectlyAligned() ? 
                                     "EXCELLENT LATCH" : "ADJUSTING LATCH...";
            Color qualityColor = alignmentSystem->IsPerfectlyAligned() ? 
                               Color{0, 200, 0, 255} : Color{255, 150, 0, 255};
            DrawText(latchQuality, pos.x - 60, pos.y + mouthRadius + 40, 14, qualityColor);
        }
    }

    void DrawAnatomicalInfo() const
    {
        if (!showLabels) return;

        const char *info[] = {
            "ULTRA-REALISTIC LACTATION MECHANICS:",
            "• Proper Alignment: Zero distance between nipple and mouth",
            "• Contact Physics: Realistic tissue deformation during latch",
            "• Milk Ejection: Pressure-driven flow with alignment optimization",
            "• Educational Focus: Anatomically accurate breastfeeding visualization"};

        int startY = 50;
        for (int i = 0; i < 5; i++)
        {
            Color color = (i == 0) ? highlightColor : textColor;
            if (i > 0 && alignmentSystem->IsPerfectlyAligned())
            {
                color = ColorBrightness(color, 0.3f);
            }
            int font = (i == 0) ? fontSize : smallFontSize;
            DrawText(info[i], 20, startY + i * 28, font, color);
        }

        // Real-time alignment feedback
        DrawAlignmentFeedback();
    }

    void DrawAlignmentFeedback() const
    {
        Rectangle feedbackBg = {20, 200, 350, 120};
        Color bgColor = alignmentSystem->IsPerfectlyAligned() ? 
                       Color{0, 100, 0, 150} : Color{100, 100, 100, 150};
        DrawRectangleRounded(feedbackBg, 0.1f, 8, bgColor);

        DrawText("REAL-TIME ALIGNMENT STATUS:", 30, 210, 14, WHITE);
        
        float distance = alignmentSystem->GetContactDistance();
        float quality = alignmentSystem->GetAlignmentQuality();
        
        DrawText(TextFormat("Contact Distance: %.1f px", distance), 30, 235, 12, WHITE);
        DrawText(TextFormat("Alignment Quality: %.1f%%", (1.0f - quality) * 100), 30, 255, 12, WHITE);
        
        const char* status = alignmentSystem->IsPerfectlyAligned() ? 
                           "✓ PERFECT CONTACT ACHIEVED" : "⚠ ADJUST POSITIONING";
        Color statusColor = alignmentSystem->IsPerfectlyAligned() ? 
                          Color{0, 255, 0, 255} : Color{255, 200, 0, 255};
        DrawText(status, 30, 280, 13, statusColor);
    }

private:
    void DrawLabelWithLeader(const char *text, Vector2 textPos, Vector2 targetPos, Color color) const
    {
        // Enhanced leader line with alignment feedback
        Color leaderColor = color;
        leaderColor.a = 180;
        float lineThickness = alignmentSystem->IsPerfectlyAligned() ? 2.0f : 1.5f;
        DrawLineEx(textPos, targetPos, lineThickness, leaderColor);

        // Enhanced text background
        int textWidth = MeasureText(text, fontSize);
        Rectangle textBg = Rectangle{(float)textPos.x - 5.0f, (float)textPos.y - 5.0f, 
                                   (float)textWidth + 10.0f, (float)fontSize + 8.0f};

        Color bgColor = alignmentSystem->IsPerfectlyAligned() ? 
                       Color{240, 255, 240, 220} : Color{255, 255, 255, 200};
        DrawRectangleRounded(textBg, 0.3f, 8, bgColor);

        // Enhanced text
        DrawText(text, textPos.x, textPos.y, fontSize, color);

        // Enhanced target point
        float pointSize = alignmentSystem->IsPerfectlyAligned() ? 4.0f : 3.0f;
        DrawCircleV(targetPos, pointSize, color);
    }

public:
    void SetShowLabels(bool show) { showLabels = show; }
    bool GetShowLabels() const { return showLabels; }
};

// Enhanced UI controller with perfect alignment controls
class UIController
{
private:
    bool showStructures;
    bool animate;
    bool showPhysiology;
    bool enableRealisticMode;
    bool showAlignmentGuides;
    bool enablePerfectAlignment;

public:
    UIController() : showStructures(true), animate(true), showPhysiology(true), 
                    enableRealisticMode(true), showAlignmentGuides(true), enablePerfectAlignment(false) {}

    void DrawUI(AnatomicalBreast &breast, BabyHead &baby, LabelSystem &labels, 
                Config &config, AlignmentSystem &alignment, ContactPhysics &contact)
    {
        rlImGuiBegin();

        if (ImGui::Begin("Ultra-Realistic Lactation Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("Advanced Medical Visualization with Perfect Alignment");
            ImGui::Separator();

            // Alignment Status Panel
            if (ImGui::CollapsingHeader("Alignment Status", ImGuiTreeNodeFlags_DefaultOpen))
            {
                bool isPerfect = alignment.IsPerfectlyAligned();
                ImGui::TextColored(isPerfect ? ImVec4(0, 1, 0, 1) : ImVec4(1, 0.5f, 0, 1), 
                                 isPerfect ? "✓ PERFECT ALIGNMENT" : "⚠ NEEDS ADJUSTMENT");
                
                float distance = alignment.GetContactDistance();
                float quality = alignment.GetAlignmentQuality();
                
                ImGui::Text("Contact Distance: %.1f px", distance);
                ImGui::ProgressBar(1.0f - quality, ImVec2(200, 0), "Alignment Quality");
                
                if (contact.IsInContact())
                {
                    ImGui::TextColored(ImVec4(0, 1, 0, 1), "✓ PHYSICAL CONTACT ESTABLISHED");
                    ImGui::Text("Deformation: %.2f", contact.GetDeformationAmount());
                }
                else
                {
                    ImGui::TextColored(ImVec4(1, 0, 0, 1), "✗ NO CONTACT");
                }
            }

            // Perfect Positioning Controls
            if (ImGui::CollapsingHeader("Perfect Positioning Controls", ImGuiTreeNodeFlags_DefaultOpen))
            {
                Vector2 breastPos = breast.GetPosition();
                Vector2 babyPos = baby.GetPosition();

                if (ImGui::SliderFloat2("Breast Position", &breastPos.x, 100, Config::SCREEN_WIDTH - 300))
                {
                    breast.SetPosition(breastPos);
                }

                if (ImGui::SliderFloat2("Baby Position", &babyPos.x, 300, Config::SCREEN_WIDTH - 100))
                {
                    baby.SetPosition(babyPos);
                }

                if (ImGui::Button("Auto-Align for Perfect Contact"))
                {
                    AutoAlignForPerfectContact(breast, baby);
                }

                ImGui::SameLine();
                if (ImGui::Button("Reset Positions"))
                {
                    breast.SetPosition({400, 450});
                    baby.SetPosition({700, 450});
                }
            }

            // Size and Anatomy Controls
            if (ImGui::CollapsingHeader("Anatomical Parameters"))
            {
                float breastSize = breast.GetRadius();
                float babyMouthSize = baby.GetMouthRadius();

                if (ImGui::SliderFloat("Breast Size", &breastSize, 120.0f, 280.0f))
                {
                    breast.SetRadius(breastSize);
                }

                if (ImGui::SliderFloat("Baby Mouth Size", &babyMouthSize, 40.0f, 90.0f))
                {
                    baby.SetMouthRadius(babyMouthSize);
                }

                ImGui::SliderFloat("Contact Deformation", &config.contactDeformationAmount, 0.0f, 0.3f);
                ImGui::SliderFloat("Alignment Threshold", &config.perfectAlignmentThreshold, 1.0f, 15.0f);
            }

            // Visual Enhancement Controls
            if (ImGui::CollapsingHeader("Visual Enhancements"))
            {
                ImGui::Checkbox("Show Alignment Guides", &config.showAlignmentGuides);
                ImGui::Checkbox("Enable Auto-Alignment", &config.enableAutoAlignment);
                ImGui::Checkbox("Realistic Physics Mode", &enableRealisticMode);
                
                bool showLabels = labels.GetShowLabels();
                if (ImGui::Checkbox("Show Educational Labels", &showLabels))
                {
                    labels.SetShowLabels(showLabels);
                }

                ImGui::Checkbox("Show Anatomical Info", &showPhysiology);
                ImGui::Checkbox("Enable Animation", &animate);
            }

            // Advanced Physics Controls
            if (ImGui::CollapsingHeader("Physics Parameters"))
            {
                ImGui::SliderFloat("Animation Speed", &config.animationSpeed, 0.1f, 3.0f);
                ImGui::SliderInt("Milk Drop Count", &config.milkDropCount, 8, 25);
                ImGui::SliderInt("Milk Streams", &config.milkStreamCount, 3, 10);
                ImGui::SliderFloat("Skin Detail", &config.skinBumpiness, 0.0f, 1.0f);
                ImGui::SliderFloat("Vein Visibility", &config.veinVisibility, 0.0f, 0.6f);
            }

            // Lighting Controls
            if (ImGui::CollapsingHeader("Lighting System"))
            {
                ImGui::SliderFloat2("Light Position", &config.lightPosition.x, 0, Config::SCREEN_WIDTH);
                ImGui::SliderFloat("Ambient Light", &config.ambientStrength, 0.1f, 0.9f);
                ImGui::SliderFloat("Diffuse Light", &config.diffuseStrength, 0.2f, 1.2f);
                ImGui::SliderFloat("Specular Light", &config.specularStrength, 0.1f, 0.8f);
            }

            ImGui::Separator();
            ImGui::TextWrapped("Educational Note: This simulation demonstrates anatomically correct "
                             "breastfeeding mechanics with zero-distance contact for optimal milk transfer.");
        }
        ImGui::End();

        rlImGuiEnd();
    }

    void AutoAlignForPerfectContact(AnatomicalBreast &breast, BabyHead &baby)
    {
        Vector2 nipplePos = breast.GetNipplePosition();
        Vector2 optimalBabyPos = {
            nipplePos.x + breast.GetAreolaRadius() + baby.GetMouthRadius() - 5.0f,
            nipplePos.y
        };
        baby.SetPosition(optimalBabyPos);
    }

    bool GetAnimate() const { return animate; }
    bool GetShowStructures() const { return showStructures; }
    bool GetShowPhysiology() const { return showPhysiology; }
    bool GetRealisticMode() const { return enableRealisticMode; }
};

// Enhanced input handler with perfect alignment features
class InputHandler
{
public:
    static bool CheckLatchInteraction(const AnatomicalBreast &breast, const BabyHead &baby, 
                                    AlignmentSystem &alignment)
    {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePos = GetMousePosition();
            Vector2 nipplePos = breast.GetNipplePosition();
            Vector2 mouthPos = baby.GetMouthPosition();
            
            float distanceToNipple = Vector2Distance(mousePos, nipplePos);
            float distanceToMouth = Vector2Distance(mousePos, mouthPos);
            
            // Enhanced latch detection with alignment consideration
            bool nearNipple = distanceToNipple < breast.GetAreolaRadius();
            bool nearMouth = distanceToMouth < baby.GetEffectiveMouthRadius() * 1.5f;
            bool perfectAlignment = alignment.IsPerfectlyAligned();
            
            return (nearNipple || nearMouth) && (perfectAlignment || alignment.GetContactDistance() < 20.0f);
        }
        return false;
    }

    static void HandleAlignmentControls(AnatomicalBreast &breast, BabyHead &baby, 
                                      AlignmentSystem &alignment, Config &config)
    {
        // Keyboard shortcuts for perfect alignment
        if (IsKeyPressed(KEY_SPACE))
        {
            // Auto-align for perfect contact
            Vector2 nipplePos = breast.GetNipplePosition();
            Vector2 optimalPos = {
                nipplePos.x + breast.GetAreolaRadius() + baby.GetMouthRadius() - 3.0f,
                nipplePos.y
            };
            baby.SetPosition(optimalPos);
        }

        // Fine-tune positioning with arrow keys
        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            Vector2 babyPos = baby.GetPosition();
            if (IsKeyPressed(KEY_LEFT)) babyPos.x -= 1.0f;
            if (IsKeyPressed(KEY_RIGHT)) babyPos.x += 1.0f;
            if (IsKeyPressed(KEY_UP)) babyPos.y -= 1.0f;
            if (IsKeyPressed(KEY_DOWN)) babyPos.y += 1.0f;
            baby.SetPosition(babyPos);
        }

        // Toggle alignment guides
        if (IsKeyPressed(KEY_G))
        {
            config.showAlignmentGuides = !config.showAlignmentGuides;
        }
    }

    static void HandleCameraControls(Config &config)
    {
        // Enhanced camera controls
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            // Could implement zoom functionality
        }

        // Pan light with right mouse button
        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
        {
            Vector2 delta = GetMouseDelta();
            config.lightPosition = Vector2Add(config.lightPosition, delta);
        }
    }
};

// Main application class with ultra-realistic features
class Application
{
private:
    Config config;
    LightingSystem lighting;
    ContactPhysics contactPhysics;
    AlignmentSystem alignmentSystem;
    AnatomicalBreast breast;
    BabyHead baby;
    MilkEjection milkEjection;
    LabelSystem labelSystem;
    UIController uiController;
    float totalTime;

    void DrawAdvancedBackground() const
    {
        // Enhanced gradient background
        Color topColor = {248, 248, 252, 255};
        Color bottomColor = {238, 238, 248, 255};
        DrawRectangleGradientV(0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, topColor, bottomColor);

        // Enhanced reference grid
        Color gridColor = {220, 220, 235, 80};
        for (int x = 0; x < Config::SCREEN_WIDTH; x += 50)
        {
            DrawLine(x, 0, x, Config::SCREEN_HEIGHT, gridColor);
        }
        for (int y = 0; y < Config::SCREEN_HEIGHT; y += 50)
        {
            DrawLine(0, y, Config::SCREEN_WIDTH, y, gridColor);
        }
    }

    void DrawEducationalDisclaimer() const
    {
        Rectangle disclaimerBg = {10, Config::SCREEN_HEIGHT - 100, Config::SCREEN_WIDTH - 20, 90};
        Color bgColor = alignmentSystem.IsPerfectlyAligned() ? 
                       Color{240, 255, 240, 240} : Color{255, 255, 255, 240};
        DrawRectangleRounded(disclaimerBg, 0.1f, 8, bgColor);

        Color borderColor = alignmentSystem.IsPerfectlyAligned() ? 
                          Color{100, 200, 100, 255} : Color{150, 100, 100, 255};
        DrawRectangleRoundedLines(disclaimerBg, 0.1f, 8, 2.0f, borderColor);

        DrawText("ULTRA-REALISTIC MEDICAL EDUCATIONAL SIMULATION - PROFESSIONAL TRAINING TOOL",
                 20, Config::SCREEN_HEIGHT - 85, 16, Color{80, 40, 40, 255});
        DrawText("Perfect Alignment Demonstration: Zero-distance contact for optimal milk transfer efficiency",
                 20, Config::SCREEN_HEIGHT - 65, 14, Color{60, 30, 30, 255});
        DrawText("Real-time Physics: Anatomically accurate tissue deformation and contact mechanics",
                 20, Config::SCREEN_HEIGHT - 45, 12, DARKGRAY);
        DrawText("Controls: SPACE = Auto-align, SHIFT+Arrows = Fine-tune, G = Toggle guides, Click+Drag = Manual positioning",
                 20, Config::SCREEN_HEIGHT - 25, 11, DARKGRAY);
    }

    void DrawPerformanceInfo() const
    {
        DrawText(TextFormat("FPS: %i", GetFPS()), Config::SCREEN_WIDTH - 100, 20, 16, DARKGREEN);
        DrawText(TextFormat("Time: %.1fs", totalTime), Config::SCREEN_WIDTH - 100, 40, 14, DARKGRAY);
        
        // Alignment status
        const char* alignmentStatus = alignmentSystem.IsPerfectlyAligned() ? "PERFECT" : "ADJUSTING";
        Color statusColor = alignmentSystem.IsPerfectlyAligned() ? DARKGREEN : ORANGE;
        DrawText(TextFormat("Alignment: %s", alignmentStatus), Config::SCREEN_WIDTH - 150, 60, 12, statusColor);
    }

public:
    Application() : lighting(&config), contactPhysics(&config), alignmentSystem(&config),
                    breast({400, 450}, 180.0f, &config, &lighting, &contactPhysics),
                    baby({700, 450}, 65.0f, &config, &lighting, &contactPhysics, &alignmentSystem),
                    milkEjection(&config, &alignmentSystem, &contactPhysics),
                    labelSystem(&alignmentSystem), totalTime(0.0f) {}

    bool Initialize()
    {
        InitWindow(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT,
                   "Ultra-Realistic Anatomical Lactation Simulation - Perfect Alignment System");
        SetTargetFPS(Config::TARGET_FPS);
        rlImGuiSetup(true);

        SetWindowState(FLAG_WINDOW_RESIZABLE);
        SetExitKey(KEY_NULL);

        return true;
    }

    void Update()
    {
        float deltaTime = GetFrameTime();
        totalTime += deltaTime;

        // Update alignment system
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

        // Handle enhanced input
        bool isLatched = InputHandler::CheckLatchInteraction(breast, baby, alignmentSystem);
        baby.SetLatched(isLatched);
        
        InputHandler::HandleAlignmentControls(breast, baby, alignmentSystem, config);
        InputHandler::HandleCameraControls(config);

        // Update all components
        if (uiController.GetAnimate())
        {
            breast.Update(deltaTime);
            baby.Update(deltaTime);
            milkEjection.Update(deltaTime);
        }

        // Update milk ejection positions with perfect alignment
        milkEjection.SetSource(breast.GetNipplePosition());
        milkEjection.SetTarget(baby.GetMouthPosition());
        milkEjection.SetActive(isLatched && alignmentSystem.IsPerfectlyAligned());
    }

    void Render()
    {
        BeginDrawing();

        DrawAdvancedBackground();

        // Draw anatomical structures with perfect alignment
        breast.Draw();
        baby.Draw();

        // Draw alignment guides
        if (config.showAlignmentGuides)
        {
            alignmentSystem.DrawAlignmentGuides(
                breast.GetPosition(), breast.GetNipplePosition(),
                baby.GetMouthPosition(), baby.GetEffectiveMouthRadius()
            );
        }

        // Draw enhanced milk ejection
        if (baby.IsLatched())
        {
            milkEjection.Draw();
        }

        // Draw educational elements
        labelSystem.DrawBreastLabels(breast);
        labelSystem.DrawBabyLabels(baby);

        if (uiController.GetShowPhysiology())
        {
            labelSystem.DrawAnatomicalInfo();
        }

        // Draw UI overlays
        DrawEducationalDisclaimer();
        DrawPerformanceInfo();

        EndDrawing();
    }

    void DrawUI()
    {
        uiController.DrawUI(breast, baby, labelSystem, config, alignmentSystem, contactPhysics);
    }

    void Cleanup()
    {
        rlImGuiShutdown();
        CloseWindow();
    }

    bool ShouldClose() const
    {
        return WindowShouldClose();
    }
};

// Main function
int main()
{
    Application app;

    if (!app.Initialize())
    {
        return -1;
    }

    while (!app.ShouldClose())
    {
        app.Update();
        app.DrawUI();
        app.Render();
    }

    app.Cleanup();
    return 0;
}