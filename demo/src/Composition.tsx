import React from "react";
import { Audio, Video } from "@remotion/media";
import { fade as fadePresentation } from "@remotion/transitions/fade";
import { linearTiming, TransitionSeries } from "@remotion/transitions";
import {
  Composition,
  Easing,
  staticFile,
  Track,
  useCurrentFrame,
  useVideoConfig,
  interpolate,
} from "remotion";

type Props = {};

const colors = {
  ink: "#071018",
  panel: "#0d1b25",
  panelLight: "#122936",
  cyan: "#58e6d3",
  lime: "#b8f06a",
  white: "#f2f7f5",
  muted: "#86a2a3",
  orange: "#ffad66",
};

const fade = (frame: number, start: number, end: number) =>
  interpolate(frame, [start, end], [0, 1], {
    extrapolateLeft: "clamp",
    extrapolateRight: "clamp",
    easing: Easing.bezier(0.16, 1, 0.3, 1),
  });

const Label = ({ children, color = colors.cyan }: { children: React.ReactNode; color?: string }) => (
  <div
    style={{
      color,
      fontFamily: "monospace",
      fontSize: 20,
      letterSpacing: 4,
      fontWeight: 700,
      textTransform: "uppercase",
    }}
  >
    {children}
  </div>
);

const GridBackground = () => (
  <div
    style={{
      position: "absolute",
      inset: 0,
      backgroundColor: colors.ink,
      backgroundImage:
        "linear-gradient(rgba(88,230,211,0.06) 1px, transparent 1px), linear-gradient(90deg, rgba(88,230,211,0.06) 1px, transparent 1px)",
      backgroundSize: "64px 64px",
    }}
  />
);

const ScanLines = () => (
  <div
    style={{
      position: "absolute",
      inset: 0,
      opacity: 0.08,
      pointerEvents: "none",
      backgroundImage: "repeating-linear-gradient(0deg, transparent 0px, transparent 5px, #ffffff 6px)",
      mixBlendMode: "screen",
    }}
  />
);

const CornerMark = ({ top, left, right, bottom }: { top?: number; left?: number; right?: number; bottom?: number }) => (
  <div
    style={{
      position: "absolute",
      top,
      left,
      right,
      bottom,
      width: 18,
      height: 18,
      borderTop: top !== undefined ? `2px solid ${colors.cyan}` : undefined,
      borderBottom: bottom !== undefined ? `2px solid ${colors.cyan}` : undefined,
      borderLeft: left !== undefined ? `2px solid ${colors.cyan}` : undefined,
      borderRight: right !== undefined ? `2px solid ${colors.cyan}` : undefined,
    }}
  />
);

const Intro = () => {
  const frame = useCurrentFrame();
  return (
    <div style={{ position: "absolute", inset: 0, display: "flex", alignItems: "center", padding: "0 150px" }}>
      <GridBackground />
      <div style={{ position: "relative", opacity: fade(frame, 0, 24) }}>
        <Label>Protocol experiment / 26.3</Label>
        <div
          style={{
            color: colors.white,
            fontFamily: "Arial, sans-serif",
            fontSize: 150,
            lineHeight: 0.86,
            fontWeight: 900,
            letterSpacing: -8,
            marginTop: 28,
          }}
        >
          MC<span style={{ color: colors.cyan }}>++</span>
        </div>
        <div style={{ color: colors.muted, fontFamily: "Arial, sans-serif", fontSize: 30, marginTop: 36 }}>
          Fast. Efficient. Responsive.
        </div>
        <div style={{ display: "flex", gap: 12, marginTop: 58 }}>
          {["HANDSHAKE", "LOGIN", "CONFIG", "PLAY"].map((item, index) => (
            <div
              key={item}
              style={{
                color: index === 3 ? colors.ink : colors.cyan,
                backgroundColor: index === 3 ? colors.cyan : "transparent",
                border: `1px solid ${colors.cyan}`,
                padding: "11px 16px",
                fontFamily: "monospace",
                fontSize: 16,
                letterSpacing: 2,
              }}
            >
              {item}
            </div>
          ))}
        </div>
      </div>
      <CornerMark top={56} left={56} />
      <CornerMark top={56} right={56} />
      <CornerMark bottom={56} left={56} />
      <CornerMark bottom={56} right={56} />
      <div style={{ position: "absolute", right: 150, bottom: 82, color: colors.muted, fontFamily: "monospace", fontSize: 16 }}>
        BUILD 0.1.0 / OFFLINE MODE
      </div>
      <ScanLines />
    </div>
  );
};

const SystemOverview = () => {
  const frame = useCurrentFrame();
  const features = [
    { title: "Protocol states", detail: "Handshake · Status · Login · Config · Play" },
    { title: "Java 26.3 world", detail: "Overworld chunks streamed around players" },
    { title: "Runtime registries", detail: "Registry and tag packets sent to the client" },
    { title: "Player movement", detail: "Move, rotate, teleport, and keep-alive packets" },
    { title: "Block interaction", detail: "Place and break supported vanilla blocks" },
    { title: "Creative inventory", detail: "Creative-mode item selection and block placement" },
    { title: "Anvil persistence", detail: "Java 26.3 world edits saved transactionally" },
    { title: "server.properties", detail: "Configure IP, port, MOTD, view distance, and world name" },
  ];
  return (
    <div style={{ position: "absolute", inset: 0, padding: "95px 120px" }}>
      <GridBackground />
      <div style={{ position: "relative", opacity: fade(frame, 0, 20) }}>
        <Label>Currently implemented</Label>
        <div style={{ color: colors.white, fontFamily: "Arial, sans-serif", fontSize: 64, fontWeight: 800, marginTop: 18 }}>
          A playable foundation.
        </div>
        <div style={{ color: colors.muted, fontFamily: "Arial, sans-serif", fontSize: 25, marginTop: 12 }}>
          The pieces already working in MC++ today.
        </div>
        <div
          style={{
            display: "grid",
            gridTemplateColumns: "repeat(4, 1fr)",
            gap: 18,
            marginTop: 48,
          }}
        >
          {features.map((feature, index) => (
            <div
              key={feature.title}
              style={{
                minHeight: 125,
                backgroundColor: colors.panel,
                border: `1px solid ${index % 2 === 0 ? colors.cyan : colors.lime}`,
                padding: "20px 22px",
                boxSizing: "border-box",
                opacity: fade(frame, index * 7, index * 7 + 16),
              }}
            >
              <div style={{ color: index % 2 === 0 ? colors.cyan : colors.lime, fontFamily: "monospace", fontSize: 21, fontWeight: 700 }}>
                {feature.title}
              </div>
              <div style={{ color: colors.muted, fontFamily: "monospace", fontSize: 16, lineHeight: 1.4, marginTop: 13 }}>
                {feature.detail}
              </div>
            </div>
          ))}
        </div>
      </div>
      <ScanLines />
    </div>
  );
};

const Motivation = () => {
  const frame = useCurrentFrame();
  return (
    <div style={{ position: "absolute", inset: 0, display: "flex", alignItems: "center", padding: "0 120px" }}>
      <GridBackground />
      <div style={{ position: "relative", width: "100%", opacity: fade(frame, 0, 20) }}>
        <Label>Motivation</Label>
        <div style={{ color: colors.white, fontFamily: "Arial, sans-serif", fontSize: 72, fontWeight: 900, marginTop: 24 }}>
          Make the protocol visible.
        </div>
        <div
          style={{
            display: "grid",
            gridTemplateColumns: "1fr 1fr",
            gap: 40,
            marginTop: 48,
          }}
        >
          <div style={{ borderLeft: `4px solid ${colors.cyan}`, padding: "8px 0 8px 28px" }}>
            <div style={{ color: colors.cyan, fontFamily: "monospace", fontSize: 20, letterSpacing: 3 }}>THE CHALLENGE</div>
            <div style={{ color: colors.white, fontFamily: "Arial, sans-serif", fontSize: 30, lineHeight: 1.35, marginTop: 18 }}>
              The server, network protocol, and world format are tightly coupled.
            </div>
          </div>
          <div style={{ borderLeft: `4px solid ${colors.lime}`, padding: "8px 0 8px 28px" }}>
            <div style={{ color: colors.lime, fontFamily: "monospace", fontSize: 20, letterSpacing: 3 }}>THE PROJECT</div>
            <div style={{ color: colors.white, fontFamily: "Arial, sans-serif", fontSize: 30, lineHeight: 1.35, marginTop: 18 }}>
              A readable C++23 implementation for studying a real Java 26.3 connection.
            </div>
          </div>
        </div>
        <div style={{ color: colors.muted, fontFamily: "monospace", fontSize: 20, marginTop: 44 }}>
          HANDSHAKE → STATUS → LOGIN → CONFIGURATION → PLAY
        </div>
      </div>
      <ScanLines />
    </div>
  );
};

const Innovation = () => {
  const frame = useCurrentFrame();
  const items = [
    ["01", "Protocol 777", "Native C++23 protocol and state-machine implementation"],
    ["02", "Anvil integration", "Existing Java 26.3 worlds with protected, transactional edits"],
    ["03", "Ack-paced chunks", "Nearby chunks first, then acknowledged view-distance streaming"],
    ["04", "Persistent profiles", "Inventory, position, rotation, and hotbar state across restarts"],
  ];
  return (
    <div style={{ position: "absolute", inset: 0, padding: "92px 120px" }}>
      <GridBackground />
      <div style={{ position: "relative", opacity: fade(frame, 0, 18) }}>
        <Label color={colors.lime}>Innovation</Label>
        <div style={{ color: colors.white, fontFamily: "Arial, sans-serif", fontSize: 66, fontWeight: 900, marginTop: 20 }}>
          Small server. Deep integration.
        </div>
        <div style={{ display: "grid", gridTemplateColumns: "1fr 1fr", gap: 22, marginTop: 44 }}>
          {items.map(([number, title, detail], index) => (
            <div
              key={title}
              style={{
                height: 170,
                boxSizing: "border-box",
                backgroundColor: colors.panel,
                border: `1px solid ${index % 2 === 0 ? colors.cyan : colors.lime}`,
                display: "flex",
                alignItems: "center",
                padding: "26px 30px",
                opacity: fade(frame, index * 8, index * 8 + 16),
              }}
            >
              <div style={{ color: index % 2 === 0 ? colors.cyan : colors.lime, fontFamily: "monospace", fontSize: 46, fontWeight: 800, width: 105 }}>
                {number}
              </div>
              <div>
                <div style={{ color: colors.white, fontFamily: "Arial, sans-serif", fontSize: 27, fontWeight: 800 }}>{title}</div>
                <div style={{ color: colors.muted, fontFamily: "Arial, sans-serif", fontSize: 20, lineHeight: 1.35, marginTop: 10 }}>{detail}</div>
              </div>
            </div>
          ))}
        </div>
      </div>
      <ScanLines />
    </div>
  );
};

const UseCases = () => {
  const frame = useCurrentFrame();
  const cases = [
    ["PROTOCOL LAB", "Test packets and state transitions with a real Java 26.3 client"],
    ["CLASSROOM", "Demonstrate registries, chunk delivery, and live block updates"],
    ["WORLD TESTING", "Load an existing world and verify edits, saves, and reconnect recovery"],
    ["FAILURE TESTS", "Exercise corrupt worlds, write failures, retries, and missing chunks"],
  ];
  return (
    <div style={{ position: "absolute", inset: 0, padding: "92px 120px" }}>
      <GridBackground />
      <div style={{ position: "relative", opacity: fade(frame, 0, 18) }}>
        <Label>Example use cases</Label>
        <div style={{ color: colors.white, fontFamily: "Arial, sans-serif", fontSize: 66, fontWeight: 900, marginTop: 20 }}>
          Built for experiments.
        </div>
        <div style={{ display: "grid", gridTemplateColumns: "1fr 1fr", gap: 20, marginTop: 44 }}>
          {cases.map(([title, detail], index) => (
            <div
              key={title}
              style={{
                minHeight: 145,
                boxSizing: "border-box",
                padding: "22px 26px",
                backgroundColor: colors.panel,
                borderTop: `3px solid ${index % 2 === 0 ? colors.cyan : colors.orange}`,
                opacity: fade(frame, index * 8, index * 8 + 16),
              }}
            >
              <div style={{ color: index % 2 === 0 ? colors.cyan : colors.orange, fontFamily: "monospace", fontSize: 20, fontWeight: 800, letterSpacing: 2 }}>
                {title}
              </div>
              <div style={{ color: colors.muted, fontFamily: "Arial, sans-serif", fontSize: 21, lineHeight: 1.35, marginTop: 13 }}>{detail}</div>
            </div>
          ))}
        </div>
      </div>
      <ScanLines />
    </div>
  );
};

const ClipSlot = ({
  title,
  detail,
  accent = colors.cyan,
  icon,
  source,
  sourceDurationLabel = "00:10",
}: {
  title: string;
  detail: string;
  accent?: string;
  icon: string;
  source?: string;
  sourceDurationLabel?: string;
}) => {
  const frame = useCurrentFrame();
  const { fps } = useVideoConfig();
  return (
    <div style={{ position: "absolute", inset: 0, padding: "74px 120px" }}>
      <GridBackground />
      <div style={{ position: "relative", opacity: fade(frame, 0, 18) }}>
        <Label color={accent}>Video demonstration</Label>
        <div style={{ color: colors.white, fontFamily: "Arial, sans-serif", fontSize: 58, fontWeight: 800, marginTop: 18 }}>
          {title}
        </div>
        <div style={{ color: colors.muted, fontFamily: "Arial, sans-serif", fontSize: 23, marginTop: 10 }}>{detail}</div>
        <div
          style={{
            position: "relative",
            marginTop: 42,
            width: 1240,
            height: 697.5,
            backgroundColor: "rgba(13,27,37,0.9)",
            border: `2px dashed ${accent}`,
            display: "flex",
            alignItems: "center",
            justifyContent: "center",
            overflow: "hidden",
          }}
        >
          <div
            style={{
              position: "absolute",
              inset: 0,
              opacity: 0.28,
              backgroundImage: "linear-gradient(135deg, transparent 46%, rgba(88,230,211,0.18) 47%, transparent 48%)",
              backgroundSize: "34px 34px",
              translate: `${interpolate(frame, [0, 180], [0, -34], { extrapolateRight: "extend" })}px 0px`,
            }}
          />
          {source ? (
          <Video
            name={`${title} footage`}
            src={staticFile(source)}
            volume={0.9}
            objectFit="cover"
            style={{
              position: "absolute",
              inset: 0,
              width: "100%",
              height: "100%",
            }}
          />
          ) : (
          <div style={{ position: "relative", textAlign: "center" }}>
            <div style={{ color: accent, fontSize: 76, fontFamily: "monospace", fontWeight: 700 }}>{icon}</div>
            <div style={{ color: colors.white, fontFamily: "monospace", fontSize: 23, letterSpacing: 3, marginTop: 16 }}>
              DROP CLIP HERE
            </div>
            <div style={{ color: colors.muted, fontFamily: "monospace", fontSize: 16, marginTop: 14 }}>
              Suggested shot: 16:9 gameplay capture
            </div>
          </div>
          )}
          {source ? (
          <div
            style={{
              position: "absolute",
              inset: 0,
              background: "linear-gradient(180deg, rgba(7,16,24,0.12) 55%, rgba(7,16,24,0.82) 100%)",
            }}
          />
          ) : null}
          <div style={{ position: "absolute", left: 22, bottom: 20, color: colors.muted, fontFamily: "monospace", fontSize: 15 }}>
          {source ? `SOURCE // ${source}` : `MEDIA SLOT // ${title.toUpperCase().split(" ").join("_")}`}
          </div>
          <div style={{ position: "absolute", right: 22, bottom: 20, color: accent, fontFamily: "monospace", fontSize: 15 }}>
            00:{String(Math.floor(frame / fps)).padStart(2, "0")} / {source ? sourceDurationLabel : "00:10"}
          </div>
        </div>
      </div>
      <ScanLines />
    </div>
  );
};

const Closing = () => {
  const frame = useCurrentFrame();
  return (
    <div style={{ position: "absolute", inset: 0, display: "flex", alignItems: "center", justifyContent: "center" }}>
      <GridBackground />
      <div style={{ position: "relative", textAlign: "center", opacity: fade(frame, 0, 26) }}>
        <div style={{ color: colors.cyan, fontFamily: "monospace", fontSize: 22, letterSpacing: 5 }}>THE WORLD IS A PACKET</div>
        <div style={{ color: colors.white, fontFamily: "Arial, sans-serif", fontSize: 88, fontWeight: 900, letterSpacing: -4, marginTop: 24 }}>
          MC<span style={{ color: colors.cyan }}>++</span>
        </div>
        <div style={{ color: colors.muted, fontFamily: "Arial, sans-serif", fontSize: 25, marginTop: 24 }}>
          Fast. Efficient. Responsive.
        </div>
        <div style={{ color: colors.lime, fontFamily: "monospace", fontSize: 18, marginTop: 54 }}>
          github.com/JasonHK-CityUHK/CS2310-Project
        </div>
        <div style={{ color: colors.muted, fontFamily: "Arial, sans-serif", fontSize: 17, marginTop: 28 }}>
          Thanks to Minecraft Wiki and wiki.vg for Minecraft Java Edition protocol and save-format information.
        </div>
      </div>
      <ScanLines />
    </div>
  );
};

export const MyComposition = () => (
  <Composition
    id="MCPlusPlusDemo"
    component={MyComponent}
    durationInFrames={1800}
    fps={30}
    width={1920}
    height={1080}
    defaultProps={{}}
  />
);

export const MyComponent: React.FC<Props> = () => {
  const frame = useCurrentFrame();
  const { fps } = useVideoConfig();
  return (
    <div style={{ position: "absolute", inset: 0, backgroundColor: colors.ink }}>
      <Track name="Music">
        <Audio
          name="English Country Garden"
          src={staticFile("English Country Garden - Aaron Kenny.mp3")}
          durationInFrames={1800}
          loop
          volume={interpolate(
            frame,
            [0, 1 * fps, 756, 774, 1650, 1668, 1800],
            [0, 0.34, 0.34, 0.12, 0.12, 0.34, 0],
            {
              extrapolateLeft: "clamp",
              extrapolateRight: "clamp",
            },
          )}
        />
      </Track>
      <Track name="Main story">
        <TransitionSeries>
          <TransitionSeries.Sequence name="Opening title" durationInFrames={5 * fps}>
            <Intro />
          </TransitionSeries.Sequence>
          <TransitionSeries.Transition presentation={fadePresentation()} timing={linearTiming({ durationInFrames: 18 })} />
          <TransitionSeries.Sequence name="Motivation" durationInFrames={6 * fps}>
            <Motivation />
          </TransitionSeries.Sequence>
          <TransitionSeries.Transition presentation={fadePresentation()} timing={linearTiming({ durationInFrames: 18 })} />
          <TransitionSeries.Sequence name="Innovation" durationInFrames={5 * fps}>
            <Innovation />
          </TransitionSeries.Sequence>
          <TransitionSeries.Transition presentation={fadePresentation()} timing={linearTiming({ durationInFrames: 18 })} />
          <TransitionSeries.Sequence name="Example use cases" durationInFrames={156}>
            <UseCases />
          </TransitionSeries.Sequence>
          <TransitionSeries.Transition presentation={fadePresentation()} timing={linearTiming({ durationInFrames: 18 })} />
          <TransitionSeries.Sequence name="System overview" durationInFrames={7 * fps}>
            <SystemOverview />
          </TransitionSeries.Sequence>
          <TransitionSeries.Transition presentation={fadePresentation()} timing={linearTiming({ durationInFrames: 18 })} />
          <TransitionSeries.Sequence name="Joining and flying full clip" durationInFrames={16 * fps}>
            <ClipSlot
              title="Join + fly through the world"
              detail="Full recording: handshake, login, configuration, and movement"
              icon="01"
              source="2026-11-24 18-38-59.mp4"
              sourceDurationLabel="00:20"
            />
          </TransitionSeries.Sequence>
          <TransitionSeries.Transition presentation={fadePresentation()} timing={linearTiming({ durationInFrames: 18 })} />
          <TransitionSeries.Sequence name="Block placing and destroying clip" durationInFrames={15 * fps}>
            <ClipSlot
              title="Creative inventory + blocks"
              detail="Full recording: select items, place blocks, break blocks, and sync updates"
              accent={colors.orange}
              icon="03"
              source="2026-11-24 18-58-46.mp4"
              sourceDurationLabel="00:15"
            />
          </TransitionSeries.Sequence>
          <TransitionSeries.Transition presentation={fadePresentation()} timing={linearTiming({ durationInFrames: 18 })} />
          <TransitionSeries.Sequence name="Closing title" durationInFrames={5 * fps}>
            <Closing />
          </TransitionSeries.Sequence>
        </TransitionSeries>
      </Track>
    </div>
  );
};
