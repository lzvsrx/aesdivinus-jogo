const $ = (selector) => document.querySelector(selector);
const $$ = (selector) => [...document.querySelectorAll(selector)];

const screens = {
  auth: $("#auth-screen"),
  register: $("#register-screen"),
  creator: $("#creator-screen"),
  loading: $("#loading-screen"),
  game: $("#game-screen"),
  ending: $("#ending-screen"),
};

const colors = {
  Gloregni: "#ffd700",
  Iusdicta: "#e0ffff",
  Satiae: "#00ff66",
  Thofestoe: "#ff4500",
  Miseritae: "#32cd32",
};

const hairColors = [
  ["Loiro nobre", "#e6c280"],
  ["Castanho", "#4a2e1b"],
  ["Ruivo", "#a03623"],
  ["Preto", "#0b0b0b"],
];

const skinColors = [
  ["Porcelana palida", "#f5e6d3"],
  ["Marfim claro", "#fff8dc"],
  ["Olivia palido", "#d3c4a5"],
  ["Bronzeado quente", "#d8a070"],
];

const personalities = [
  { id: "Bravura", color: "#990000", desc: "Forca sob pressao. Ao colapsar, recupera 50% da coragem." },
  { id: "Autocrata", color: "#4b0082", desc: "Ordens mais fortes, mas lealdade cai mais rapido." },
  { id: "Prudente", color: "#003366", desc: "Mais percepcao e esquiva mais segura." },
  { id: "Perfeccionista", color: "#ffbf00", desc: "Criticos melhores, exige coragem alta." },
];

const routes = [
  {
    id: 1,
    title: "Rota 1 - Pesado / Area",
    weapon: "Espada de 2 maos e martelo",
    armor: "Pesada, bracelete e capacete",
    mods: { forca: 5, coragem: 2, percepcao: -5, inspiracao: -2 },
    trait: "Bravura e determinado / impulsivo e arrogante",
  },
  {
    id: 2,
    title: "Rota 2 - Equilibrado / Defensivo",
    weapon: "Espada de 1 mao e escudo",
    armor: "Mista, escudo de armas",
    mods: { inspiracao: 5, forca: 2, agilidade: -5, percepcao: -1 },
    trait: "Compromisso e transparencia / autoritarismo e arrogancia",
  },
  {
    id: 3,
    title: "Rota 3 - Alcance / Tatico",
    weapon: "Lanca longa",
    armor: "Leve, manto de batalha",
    mods: { percepcao: 5, inspiracao: 1, forca: -5, coragem: -1 },
    trait: "Prudencia e sabio / arrogante e desconsiderado",
  },
  {
    id: 4,
    title: "Rota 4 - Critico / Dual",
    weapon: "Duas espadas leves",
    armor: "Malha e luvas de couro",
    mods: { agilidade: 5, percepcao: 2, forca: -5, coragem: -2 },
    trait: "Compromisso e disciplinado / arrogancia e perfeccionista",
  },
  {
    id: 5,
    title: "Rota 5 - Agilidade / Furtivo",
    weapon: "Lanca leve",
    armor: "Malha e cinto de utilitarios",
    mods: { agilidade: 5, percepcao: 2, forca: -5, inspiracao: -2 },
    trait: "Destreza e versatil / hipocrita e arrogante",
  },
];

const chapters = [
  {
    id: "1.1",
    name: "Entrada na Floresta Wood",
    location: "Caminho entre King's Lynn e Foxley Wood",
    weather: "sun",
    goal: 880,
    enemies: [
      { type: "Homines Corrupti", x: 420, hp: 52, speed: 52, damage: 10, corrupted: true },
      { type: "Barbari Cruenti", x: 670, hp: 68, speed: 42, damage: 13, corrupted: true },
    ],
    dialogue: {
      speaker: "Ethan Armand",
      text: "A floresta esta quieta demais para uma marcha de trezentos homens.",
      choices: [
        { text: "Avancar com escudos", effect: { loyalty: 8, courage: 4, order: "shield" } },
        { text: "Enviar Donovan a frente", effect: { perception: 2, courage: -4, order: "archers" } },
      ],
    },
  },
  {
    id: "1.2",
    name: "Clareira da Emboscada",
    location: "Arena de combate",
    weather: "fog",
    goal: 980,
    enemies: [
      { type: "Barbaro Lobo", x: 390, hp: 85, speed: 70, damage: 16, corrupted: true },
      { type: "Canis Ferox", x: 760, hp: 132, speed: 84, damage: 20, corrupted: true, boss: true },
    ],
    dialogue: {
      speaker: "Donovan Michael",
      text: "O machado veio das arvores. O cavalo do principe caiu!",
      choices: [
        { text: "Reagrupar sobreviventes", effect: { loyalty: 10, courage: 8, order: "shield" } },
        { text: "Perseguir o arremessador", effect: { agility: 2, loyalty: -6, order: "charge" } },
      ],
    },
  },
  {
    id: "1.3",
    name: "Massacre do Exercito",
    location: "Floresta devastada",
    weather: "blood",
    goal: 1040,
    enemies: [
      { type: "Servi Belli Larvae", x: 430, hp: 96, speed: 38, damage: 18, corrupted: true },
      { type: "Ogre Larva Belli", x: 840, hp: 230, speed: 34, damage: 28, corrupted: true, boss: true },
    ],
    dialogue: {
      speaker: "Duque Elric",
      text: "William, de pe! Se cairmos aqui, Gradon nao tera aviso.",
      choices: [
        { text: "Despertar Gloregni", effect: { brand: "Gloregni", loyalty: 25, inspiration: 5 } },
        { text: "Usar Iusdicta contra o horror", effect: { brand: "Iusdicta", strength: 3, perception: 3 } },
        { text: "Forjar caminho com Thofestoe", effect: { brand: "Thofestoe", ore: 2 } },
      ],
    },
  },
];

const companions = [
  { name: "Hilda de Augusto", role: "Tatica nobre", loyalty: 82 },
  { name: "Elric Legrand", role: "Mentor e duque", loyalty: 92 },
  { name: "Ethan Armand", role: "Vanguarda pesada", loyalty: 78 },
  { name: "Donovan Michael", role: "Batedor agil", loyalty: 74 },
  { name: "Albert Roberts", role: "Defensor robusto", loyalty: 80 },
  { name: "Isabeau Moreau", role: "Santa guerreira", loyalty: 86 },
];

const loreCards = [
  "O minerio Aes Divinus corta carne comum como aco, mas queima a corrupcao como julgamento vivo.",
  "Gloregni fortalece lideres e acorda marcas proximas; Iusdicta troca olhos fisicos por visao astral.",
  "A chuva de sangue aumenta a furia dos corrompidos. Sol aberto favorece comandantes abencoados.",
];

const state = {
  screen: "auth",
  graphics: localStorage.getItem("aes_graphics") || "low",
  reduceVfx: localStorage.getItem("aes_reduce_vfx") === "true",
  volume: Number(localStorage.getItem("aes_volume") || 60),
  profile: {
    name: "William de Augusto",
    hair: hairColors[0][1],
    skin: skinColors[0][1],
    personality: "Bravura",
    route: 2,
  },
  stats: {},
  chapterIndex: 0,
  ore: 0,
  crafted: [],
  activeBrands: [],
  order: "shield",
  paused: false,
  inDialogue: false,
  gameOver: false,
};

const game = {
  canvas: $("#game-canvas"),
  ctx: $("#game-canvas").getContext("2d"),
  w: 1280,
  h: 720,
  keys: new Set(),
  last: 0,
  cameraX: 0,
  particles: [],
  enemies: [],
  projectiles: [],
  player: {
    x: 80,
    y: 550,
    vx: 0,
    vy: 0,
    w: 44,
    h: 92,
    facing: 1,
    grounded: true,
    attackCd: 0,
    dodgeCd: 0,
    invuln: 0,
    hp: 100,
    courage: 100,
    loyalty: 100,
  },
};

function showScreen(name) {
  state.screen = name;
  Object.entries(screens).forEach(([key, el]) => el.classList.toggle("active", key === name));
}

function initMenus() {
  $("#hair-color").innerHTML = "";
  $("#skin-color").innerHTML = "";
  hairColors.forEach(([label, value]) => $("#hair-color").append(new Option(label, value)));
  skinColors.forEach(([label, value]) => $("#skin-color").append(new Option(label, value)));
  $("#hair-color").value = state.profile.hair;
  $("#skin-color").value = state.profile.skin;
  $("#graphics-mode").value = state.graphics;
  $("#reduce-vfx").checked = state.reduceVfx;
  $("#volume").value = state.volume;

  $("#personality-options").innerHTML = personalities.map((p) => `
    <button class="option-card ${p.id === state.profile.personality ? "active" : ""}" data-personality="${p.id}" type="button">
      <strong style="color:${p.color}">${p.id}</strong><br><small>${p.desc}</small>
    </button>`).join("");

  $("#route-options").innerHTML = routes.map((r) => `
    <button class="route-card ${r.id === state.profile.route ? "active" : ""}" data-route="${r.id}" type="button">
      <strong>${r.title}</strong><br><small>${r.weapon} · ${r.armor}</small><br><small>${r.trait}</small>
    </button>`).join("");

  updateAvatar();
  updateStatsPreview();
}

function bindUi() {
  $("#login-form").addEventListener("submit", (event) => {
    event.preventDefault();
    showScreen("creator");
  });
  $("#show-register").addEventListener("click", () => showScreen("register"));
  $("#back-login").addEventListener("click", () => showScreen("auth"));
  $("#register-form").addEventListener("submit", (event) => {
    event.preventDefault();
    if ($("#reg-password").value !== $("#reg-confirm").value) {
      alert("A confirmacao de senha nao confere.");
      return;
    }
    $("#login-email").value = $("#reg-email").value;
    showScreen("creator");
  });
  $("#open-settings-auth").addEventListener("click", () => $("#settings-dialog").showModal());
  $("#pause-button").addEventListener("click", toggleDrawer);
  $("#close-drawer").addEventListener("click", () => $("#side-drawer").classList.remove("open"));
  $("#restart").addEventListener("click", () => {
    state.chapterIndex = 0;
    state.ore = 0;
    state.crafted = [];
    state.activeBrands = [];
    showScreen("creator");
  });

  $("#graphics-mode").addEventListener("change", (event) => {
    state.graphics = event.target.value;
    localStorage.setItem("aes_graphics", state.graphics);
  });
  $("#reduce-vfx").addEventListener("change", (event) => {
    state.reduceVfx = event.target.checked;
    localStorage.setItem("aes_reduce_vfx", state.reduceVfx);
  });
  $("#volume").addEventListener("input", (event) => {
    state.volume = Number(event.target.value);
    localStorage.setItem("aes_volume", state.volume);
  });

  $$(".tab").forEach((tab) => tab.addEventListener("click", () => {
    $$(".tab").forEach((t) => t.classList.remove("active"));
    $$(".tab-page").forEach((page) => page.classList.remove("active"));
    tab.classList.add("active");
    $(`#tab-${tab.dataset.tab}`).classList.add("active");
  }));

  $("#char-name").addEventListener("input", (event) => {
    state.profile.name = event.target.value || "William";
  });
  $("#hair-color").addEventListener("change", (event) => {
    state.profile.hair = event.target.value;
    updateAvatar();
  });
  $("#skin-color").addEventListener("change", (event) => {
    state.profile.skin = event.target.value;
    updateAvatar();
  });
  $("#personality-options").addEventListener("click", (event) => {
    const card = event.target.closest("[data-personality]");
    if (!card) return;
    state.profile.personality = card.dataset.personality;
    initMenus();
  });
  $("#route-options").addEventListener("click", (event) => {
    const card = event.target.closest("[data-route]");
    if (!card) return;
    state.profile.route = Number(card.dataset.route);
    initMenus();
  });
  $("#start-game").addEventListener("click", startLoading);

  $("#squad-panel").addEventListener("click", (event) => {
    const button = event.target.closest("[data-order]");
    if (button) setOrder(button.dataset.order);
  });

  window.addEventListener("keydown", (event) => {
    if (["Space", "ArrowUp", "ArrowDown"].includes(event.code)) event.preventDefault();
    game.keys.add(event.code);
    if (state.screen !== "game") return;
    if (event.code === "KeyP") toggleDrawer();
    if (event.code === "Digit1") setOrder("shield");
    if (event.code === "Digit2") setOrder("archers");
    if (event.code === "Digit3") setOrder("charge");
    if (event.code === "KeyE") interact();
  });
  window.addEventListener("keyup", (event) => game.keys.delete(event.code));
  window.addEventListener("resize", resizeCanvas);
}

function baseStats() {
  const stats = { forca: 10, agilidade: 10, coragem: 10, percepcao: 10, inspiracao: 10 };
  const route = routes.find((r) => r.id === state.profile.route);
  Object.entries(route.mods).forEach(([key, value]) => stats[key] += value);
  if (state.profile.personality === "Bravura") stats.coragem += 3;
  if (state.profile.personality === "Prudente") stats.percepcao += 3;
  if (state.profile.personality === "Perfeccionista") stats.agilidade += 2;
  if (state.profile.personality === "Autocrata") stats.inspiracao += 2;
  return stats;
}

function updateStatsPreview() {
  const stats = baseStats();
  $("#stats-preview").innerHTML = Object.entries(stats)
    .map(([key, value]) => `<dt>${labelStat(key)}</dt><dd>${value}</dd>`)
    .join("");
}

function labelStat(key) {
  return ({ forca: "Forca", agilidade: "Agilidade", coragem: "Coragem", percepcao: "Percepcao", inspiracao: "Inspiracao" })[key];
}

function updateAvatar() {
  $("#avatar").style.setProperty("--hair", state.profile.hair);
  $("#avatar").style.setProperty("--skin", state.profile.skin);
}

function startLoading() {
  state.stats = baseStats();
  state.chapterIndex = 0;
  game.player.hp = 100;
  game.player.courage = 100;
  game.player.loyalty = 100;
  game.player.x = 80;
  game.player.vx = 0;
  game.player.vy = 0;
  state.gameOver = false;
  $("#lore-card").textContent = loreCards[Math.floor(Math.random() * loreCards.length)];
  showScreen("loading");
  let progress = 0;
  const timer = setInterval(() => {
    progress += 12 + Math.random() * 18;
    $("#loading-bar").style.width = `${Math.min(progress, 100)}%`;
    if (progress >= 100) {
      clearInterval(timer);
      $("#loading-bar").style.width = "0";
      startGame();
    }
  }, 120);
}

function startGame() {
  resizeCanvas();
  showScreen("game");
  state.paused = false;
  loadChapter(0);
  requestAnimationFrame(loop);
}

function loadChapter(index) {
  state.chapterIndex = index;
  const chapter = chapters[index];
  game.player.x = 80;
  game.player.y = 550;
  game.player.vx = 0;
  game.player.vy = 0;
  game.cameraX = 0;
  game.enemies = chapter.enemies.map((enemy) => ({ ...enemy, maxHp: enemy.hp, y: 560, hitCd: 0, alive: true }));
  game.particles = [];
  game.projectiles = [];
  state.inDialogue = true;
  showDialogue(chapter.dialogue);
  updateHud();
  saveGame();
}

function showDialogue(dialogue) {
  $("#dialogue-speaker").textContent = dialogue.speaker;
  $("#dialogue-text").textContent = dialogue.text;
  $("#choices").innerHTML = dialogue.choices.map((choice, index) => `<button data-choice="${index}" type="button">${choice.text}</button>`).join("");
  $("#dialogue").classList.remove("hidden");
  $("#choices").onclick = (event) => {
    const button = event.target.closest("[data-choice]");
    if (!button) return;
    applyChoice(dialogue.choices[Number(button.dataset.choice)].effect);
    $("#dialogue").classList.add("hidden");
    state.inDialogue = false;
  };
}

function applyChoice(effect) {
  if (effect.loyalty) game.player.loyalty = clamp(game.player.loyalty + effect.loyalty, 0, 100);
  if (effect.courage) game.player.courage = clamp(game.player.courage + effect.courage, 0, 100);
  if (effect.perception) state.stats.percepcao += effect.perception;
  if (effect.agility) state.stats.agilidade += effect.agility;
  if (effect.strength) state.stats.forca += effect.strength;
  if (effect.inspiration) state.stats.inspiracao += effect.inspiration;
  if (effect.ore) state.ore += effect.ore;
  if (effect.order) setOrder(effect.order);
  if (effect.brand) activateBrand(effect.brand);
  updateHud();
}

function activateBrand(brand) {
  if (!state.activeBrands.includes(brand)) state.activeBrands.push(brand);
  if (brand === "Gloregni") {
    state.stats.inspiracao += 5;
    game.player.loyalty = clamp(game.player.loyalty + 25, 0, 100);
  }
  if (brand === "Iusdicta") {
    state.stats.forca += 3;
    state.stats.percepcao += 3;
  }
  if (brand === "Satiae") state.stats.percepcao += 5;
  if (brand === "Miseritae") game.player.hp = clamp(game.player.hp + 36, 0, 100);
  if (brand === "Thofestoe") state.ore += 1;
  burst(game.player.x, game.player.y - 65, colors[brand] || "#fff", 18);
}

function setOrder(order) {
  state.order = order;
  $$("#squad-panel button").forEach((button) => button.classList.toggle("active", button.dataset.order === order));
  if (order === "shield") game.player.loyalty = clamp(game.player.loyalty + 1, 0, 100);
  if (order === "charge") game.player.courage = clamp(game.player.courage - 1, 0, 100);
  updateHud();
}

function interact() {
  if (state.paused || state.inDialogue) return;
  const forgeNear = Math.abs(game.player.x - 250) < 70 && state.chapterIndex >= 1;
  if (forgeNear) openForge();
}

function openForge() {
  const canCraft = state.ore >= 2 && !state.crafted.includes("Lamina Aes");
  $("#drawer-content").innerHTML = `
    <h3>Forja de Robert Smith</h3>
    <p>Minerio Aes Divinus: <strong>${state.ore}</strong></p>
    <div class="mini-card">Lamina Aes: +12 dano contra corrompidos e brilho divino.</div>
    <button id="craft-aes" class="success" ${canCraft ? "" : "disabled"} type="button">FORJAR LAMINA AES</button>
    <h3>Companions</h3>
    ${companions.map((c) => `<div class="mini-card"><strong>${c.name}</strong><br>${c.role}<br>Lealdade: ${Math.round(Math.min(c.loyalty, game.player.loyalty))}%</div>`).join("")}
  `;
  $("#side-drawer").classList.add("open");
  const craftButton = $("#craft-aes");
  if (craftButton) craftButton.addEventListener("click", () => {
    state.ore -= 2;
    state.crafted.push("Lamina Aes");
    activateBrand("Thofestoe");
    openForge();
  });
}

function toggleDrawer() {
  const drawer = $("#side-drawer");
  if (drawer.classList.contains("open")) {
    drawer.classList.remove("open");
    state.paused = false;
    return;
  }
  state.paused = true;
  const route = routes.find((r) => r.id === state.profile.route);
  $("#drawer-content").innerHTML = `
    <h3>Pausa</h3>
    <div class="mini-card"><strong>${state.profile.name}</strong><br>${state.profile.personality}<br>${route.title}</div>
    <div class="mini-card"><strong>Arma</strong><br>${route.weapon}${state.crafted.length ? "<br>Lamina Aes forjada" : ""}</div>
    <div class="mini-card"><strong>Marcas</strong><br>${state.activeBrands.join(", ") || "Nenhuma ativa"}</div>
    <div class="mini-card"><strong>Minérios</strong><br>${state.ore}</div>
    <button id="settings-pause" class="outline" type="button">CONFIGURACOES</button>
    <button id="save-now" class="success" type="button">SALVAR</button>
  `;
  drawer.classList.add("open");
  $("#settings-pause").addEventListener("click", () => $("#settings-dialog").showModal());
  $("#save-now").addEventListener("click", saveGame);
}

function resizeCanvas() {
  const ratio = Math.min(window.devicePixelRatio || 1, state.graphics === "ultra" ? 2 : 1.25);
  game.canvas.width = Math.floor(window.innerWidth * ratio);
  game.canvas.height = Math.floor(window.innerHeight * ratio);
  game.ctx.setTransform(ratio, 0, 0, ratio, 0, 0);
  game.w = window.innerWidth;
  game.h = window.innerHeight;
}

function loop(timestamp) {
  if (state.screen !== "game") return;
  const dt = Math.min((timestamp - game.last) / 1000 || 0, 0.033);
  game.last = timestamp;
  if (!state.paused && !state.inDialogue && !state.gameOver) update(dt);
  render();
  requestAnimationFrame(loop);
}

function update(dt) {
  const p = game.player;
  const speed = 220 + state.stats.agilidade * 4;
  const left = game.keys.has("KeyA") || game.keys.has("ArrowLeft");
  const right = game.keys.has("KeyD") || game.keys.has("ArrowRight");
  p.vx = (right ? speed : 0) - (left ? speed : 0);
  if (p.vx !== 0) p.facing = Math.sign(p.vx);
  if ((game.keys.has("Space") || game.keys.has("KeyW")) && p.grounded) {
    p.vy = -560;
    p.grounded = false;
  }
  if (game.keys.has("KeyJ")) attack();
  if (game.keys.has("KeyK")) dodge();

  p.vy += 1450 * dt;
  p.x = clamp(p.x + p.vx * dt, 30, chapters[state.chapterIndex].goal + 180);
  p.y += p.vy * dt;
  if (p.y >= 550) {
    p.y = 550;
    p.vy = 0;
    p.grounded = true;
  }
  p.attackCd = Math.max(0, p.attackCd - dt);
  p.dodgeCd = Math.max(0, p.dodgeCd - dt);
  p.invuln = Math.max(0, p.invuln - dt);

  updateEnemies(dt);
  updateParticles(dt);
  updateProjectiles(dt);
  game.cameraX = clamp(p.x - game.w * 0.38, 0, chapters[state.chapterIndex].goal - game.w * 0.62);

  if (p.courage <= 0) courageCollapse();
  if (p.hp <= 0) finishGame(false);
  if (game.enemies.every((e) => !e.alive) && p.x >= chapters[state.chapterIndex].goal) nextChapter();
  updateHud();
}

function attack() {
  const p = game.player;
  if (p.attackCd > 0) return;
  p.attackCd = state.profile.route === 4 ? 0.24 : 0.36;
  const reach = state.profile.route === 3 || state.profile.route === 5 ? 98 : 70;
  const baseDamage = 18 + state.stats.forca * 1.5 + (state.crafted.includes("Lamina Aes") ? 12 : 0);
  let hit = false;
  game.enemies.forEach((enemy) => {
    if (!enemy.alive) return;
    const inFront = Math.sign(enemy.x - p.x) === p.facing || Math.abs(enemy.x - p.x) < 20;
    if (inFront && Math.abs(enemy.x - p.x) < reach && Math.abs(enemy.y - p.y) < 95) {
      const aesBonus = enemy.corrupted ? 1.8 : 1;
      const crit = state.profile.personality === "Perfeccionista" && p.courage > 40 && Math.random() < 0.25 ? 1.7 : 1;
      enemy.hp -= baseDamage * aesBonus * crit;
      enemy.hitCd = 0.14;
      hit = true;
      burst(enemy.x, enemy.y - 48, enemy.corrupted ? "#2e8b57" : "#d4af37", state.reduceVfx ? 5 : 12);
      if (enemy.hp <= 0) {
        enemy.alive = false;
        state.ore += enemy.boss ? 2 : 1;
        p.courage = clamp(p.courage + 6, 0, 100);
      }
    }
  });
  if (!hit) p.courage = clamp(p.courage - 1.5, 0, 100);
}

function dodge() {
  const p = game.player;
  if (p.dodgeCd > 0) return;
  p.dodgeCd = 0.75;
  p.invuln = state.profile.personality === "Prudente" ? 0.42 : 0.26;
  p.x += p.facing * (96 + state.stats.agilidade * 3);
  burst(p.x, p.y - 38, "#708090", state.reduceVfx ? 3 : 8);
}

function updateEnemies(dt) {
  const p = game.player;
  const weather = chapters[state.chapterIndex].weather;
  const weatherDamage = weather === "blood" ? 1.25 : 1;
  game.enemies.forEach((enemy) => {
    if (!enemy.alive) return;
    const dist = p.x - enemy.x;
    const orderMod = state.order === "shield" ? 0.78 : state.order === "charge" ? 1.14 : 1;
    enemy.x += Math.sign(dist) * enemy.speed * orderMod * dt;
    enemy.hitCd = Math.max(0, enemy.hitCd - dt);
    if (Math.abs(dist) < 52 && p.invuln <= 0) {
      p.hp = clamp(p.hp - enemy.damage * weatherDamage * dt, 0, 100);
      p.courage = clamp(p.courage - (enemy.boss ? 10 : 5) * dt, 0, 100);
      if (state.profile.personality === "Autocrata") p.loyalty = clamp(p.loyalty - 2.4 * dt, 0, 100);
      else p.loyalty = clamp(p.loyalty - 1.2 * dt, 0, 100);
    }
  });
  if (state.order === "archers") {
    if (Math.random() < dt * 1.5) {
      const target = game.enemies.find((e) => e.alive);
      if (target) game.projectiles.push({ x: game.player.x - 140, y: 410, target, vx: 520 });
    }
  }
}

function updateProjectiles(dt) {
  game.projectiles = game.projectiles.filter((arrow) => {
    arrow.x += arrow.vx * dt;
    arrow.y += (arrow.target.y - 65 - arrow.y) * dt * 2;
    if (!arrow.target.alive) return false;
    if (Math.abs(arrow.x - arrow.target.x) < 20) {
      arrow.target.hp -= 11 + state.stats.inspiracao * 0.45;
      burst(arrow.target.x, arrow.target.y - 64, "#d4af37", 5);
      if (arrow.target.hp <= 0) {
        arrow.target.alive = false;
        state.ore += arrow.target.boss ? 2 : 1;
      }
      return false;
    }
    return arrow.x < game.player.x + 900;
  });
}

function courageCollapse() {
  if (state.profile.personality === "Bravura") {
    game.player.courage = 50;
    state.stats.forca += 2;
    activateBrand("Gloregni");
  } else {
    game.player.courage = 18;
    game.player.loyalty = clamp(game.player.loyalty - 30, 0, 100);
    if (game.player.loyalty < 50) burst(game.player.x, game.player.y - 70, "#ff3333", 20);
  }
}

function nextChapter() {
  if (state.chapterIndex < chapters.length - 1) {
    loadChapter(state.chapterIndex + 1);
    return;
  }
  finishGame(true);
}

function finishGame(victory) {
  state.gameOver = true;
  showScreen("ending");
  $("#ending-summary").textContent = victory
    ? "William sobreviveu ao massacre e carrega o aviso ate Gradon. O exercito caiu, mas a chama Aes Divinus permaneceu."
    : "William tombou antes de alcançar Gradon. Reconfigure rota, taticas e marcas para resistir ao prologo.";
  $("#ending-stats").innerHTML = `
    <div>HP final: ${Math.round(game.player.hp)}%</div>
    <div>Coragem final: ${Math.round(game.player.courage)}%</div>
    <div>Lealdade final: ${Math.round(game.player.loyalty)}%</div>
    <div>Minerio coletado: ${state.ore}</div>
    <div>Marcas ativas: ${state.activeBrands.join(", ") || "nenhuma"}</div>
  `;
}

function updateParticles(dt) {
  game.particles = game.particles.filter((particle) => {
    particle.x += particle.vx * dt;
    particle.y += particle.vy * dt;
    particle.life -= dt;
    return particle.life > 0;
  });
}

function burst(x, y, color, count) {
  if (state.reduceVfx) count = Math.ceil(count * 0.45);
  for (let i = 0; i < count; i++) {
    game.particles.push({
      x,
      y,
      vx: (Math.random() - 0.5) * 220,
      vy: (Math.random() - 0.5) * 180,
      color,
      life: 0.25 + Math.random() * 0.45,
    });
  }
}

function render() {
  const ctx = game.ctx;
  ctx.clearRect(0, 0, game.w, game.h);
  drawBackground(ctx);
  ctx.save();
  ctx.translate(-game.cameraX, 0);
  drawWorld(ctx);
  drawPlayer(ctx, game.player);
  game.enemies.forEach((enemy) => enemy.alive && drawEnemy(ctx, enemy));
  drawProjectiles(ctx);
  drawParticles(ctx);
  ctx.restore();
  drawWeather(ctx);
}

function drawBackground(ctx) {
  const chapter = chapters[state.chapterIndex] || chapters[0];
  const grad = ctx.createLinearGradient(0, 0, 0, game.h);
  if (chapter.weather === "blood") {
    grad.addColorStop(0, "#3b1111");
    grad.addColorStop(1, "#0c0706");
  } else if (chapter.weather === "fog") {
    grad.addColorStop(0, "#172233");
    grad.addColorStop(1, "#07100d");
  } else {
    grad.addColorStop(0, "#162819");
    grad.addColorStop(1, "#08100a");
  }
  ctx.fillStyle = grad;
  ctx.fillRect(0, 0, game.w, game.h);
  const layerCount = state.graphics === "low" ? 2 : 4;
  for (let layer = 0; layer < layerCount; layer++) {
    const offset = -(game.cameraX * (0.08 + layer * 0.04)) % 220;
    ctx.fillStyle = layer % 2 ? "#102018" : "#0b1712";
    for (let x = offset - 80; x < game.w + 220; x += 110) {
      const trunk = 10 + layer * 3;
      ctx.fillRect(x, 160 + layer * 44, trunk, game.h);
      ctx.beginPath();
      ctx.ellipse(x + trunk / 2, 160 + layer * 48, 52 + layer * 12, 90, 0, 0, Math.PI * 2);
      ctx.fill();
    }
  }
}

function drawWorld(ctx) {
  const chapter = chapters[state.chapterIndex];
  ctx.fillStyle = "#1a1612";
  ctx.fillRect(-200, 640, chapter.goal + 800, 140);
  ctx.fillStyle = "#2a2218";
  for (let x = -200; x < chapter.goal + 700; x += 70) {
    ctx.fillRect(x, 635 + Math.sin(x) * 5, 44, 9);
  }
  if (state.chapterIndex >= 1) {
    ctx.fillStyle = "#3b2219";
    ctx.fillRect(220, 560, 64, 80);
    ctx.fillStyle = "#ff9933";
    ctx.fillRect(238, 534, 28, 28);
    ctx.fillStyle = "#c59b27";
    ctx.fillText("Forja", 229, 526);
  }
  ctx.fillStyle = "#d4af37";
  ctx.fillRect(chapter.goal, 520, 8, 120);
  ctx.fillText("Gradon", chapter.goal - 20, 504);
}

function drawPlayer(ctx, p) {
  const flash = p.invuln > 0 && Math.floor(p.invuln * 18) % 2 === 0;
  if (flash) ctx.globalAlpha = 0.45;
  ctx.save();
  ctx.translate(p.x, p.y);
  ctx.scale(p.facing, 1);
  ctx.fillStyle = state.profile.skin;
  ctx.fillRect(-14, -92, 28, 32);
  ctx.fillStyle = state.profile.hair;
  ctx.fillRect(-18, -100, 36, 16);
  ctx.fillStyle = "#4a4e5a";
  ctx.fillRect(-22, -58, 44, 58);
  ctx.fillStyle = "#002366";
  ctx.fillRect(-15, -50, 30, 50);
  ctx.fillStyle = "#2e8b57";
  ctx.fillRect(-3, -58, 6, 58);
  ctx.fillStyle = "#1b365d";
  ctx.fillRect(-9, -80, 4, 4);
  ctx.fillStyle = "#ffd700";
  ctx.fillRect(5, -80, 4, 4);
  ctx.strokeStyle = state.crafted.includes("Lamina Aes") ? "#2e8b57" : "#d4af37";
  ctx.lineWidth = 5;
  ctx.beginPath();
  ctx.moveTo(18, -48);
  ctx.lineTo(68, -88);
  ctx.stroke();
  if (p.attackCd > 0.18) {
    ctx.strokeStyle = "#d4af37";
    ctx.lineWidth = 3;
    ctx.beginPath();
    ctx.arc(26, -55, 70, -0.7, 0.55);
    ctx.stroke();
  }
  ctx.restore();
  ctx.globalAlpha = 1;
}

function drawEnemy(ctx, enemy) {
  ctx.save();
  ctx.translate(enemy.x, enemy.y);
  ctx.fillStyle = enemy.hitCd > 0 ? "#ff3333" : enemy.boss ? "#0d0202" : "#b22222";
  const scale = enemy.boss ? 1.35 : 1;
  ctx.scale(scale, scale);
  ctx.fillRect(-24, -72, 48, 72);
  ctx.fillStyle = enemy.boss ? "#ff3300" : "#300030";
  ctx.fillRect(-18, -98, 36, 28);
  ctx.fillStyle = "#ff0000";
  ctx.fillRect(-10, -87, 6, 6);
  ctx.fillRect(5, -87, 6, 6);
  ctx.strokeStyle = "#5a5a5a";
  ctx.lineWidth = 6;
  ctx.beginPath();
  ctx.moveTo(18, -38);
  ctx.lineTo(48, -8);
  ctx.stroke();
  ctx.restore();
  ctx.fillStyle = "#222";
  ctx.fillRect(enemy.x - 34, enemy.y - 126, 68, 8);
  ctx.fillStyle = enemy.boss ? "#ff4500" : "#8b0000";
  ctx.fillRect(enemy.x - 34, enemy.y - 126, 68 * Math.max(enemy.hp / enemy.maxHp, 0), 8);
  ctx.fillStyle = "#eee8aa";
  ctx.font = "12px Segoe UI";
  ctx.fillText(enemy.type, enemy.x - 42, enemy.y - 134);
}

function drawProjectiles(ctx) {
  ctx.strokeStyle = "#d4af37";
  ctx.lineWidth = 2;
  game.projectiles.forEach((arrow) => {
    ctx.beginPath();
    ctx.moveTo(arrow.x - 16, arrow.y);
    ctx.lineTo(arrow.x + 16, arrow.y - 2);
    ctx.stroke();
  });
}

function drawParticles(ctx) {
  game.particles.forEach((particle) => {
    ctx.globalAlpha = Math.max(particle.life, 0);
    ctx.fillStyle = particle.color;
    ctx.fillRect(particle.x, particle.y, 4, 4);
  });
  ctx.globalAlpha = 1;
}

function drawWeather(ctx) {
  const chapter = chapters[state.chapterIndex] || chapters[0];
  if (chapter.weather === "fog") {
    ctx.fillStyle = "rgba(180, 190, 205, 0.08)";
    for (let i = 0; i < 8; i++) ctx.fillRect((i * 190 - game.cameraX * 0.2) % (game.w + 190) - 90, 180 + i * 40, 260, 32);
  }
  if (chapter.weather === "blood") {
    ctx.strokeStyle = "rgba(139, 0, 0, 0.45)";
    for (let i = 0; i < 80; i++) {
      const x = (i * 37 + performance.now() * 0.04) % game.w;
      const y = (i * 91 + performance.now() * 0.22) % game.h;
      ctx.beginPath();
      ctx.moveTo(x, y);
      ctx.lineTo(x - 4, y + 18);
      ctx.stroke();
    }
  }
}

function updateHud() {
  $("#hp-fill").style.width = `${game.player.hp}%`;
  $("#courage-fill").style.width = `${game.player.courage}%`;
  const loyalty = Math.round(game.player.loyalty);
  const loyaltyColor = loyalty >= 75 ? "#00ff7f" : loyalty >= 50 ? "#ffd700" : "#ff0000";
  $("#loyalty-meter").style.background = `conic-gradient(${loyaltyColor} ${loyalty * 3.6}deg, #252525 0)`;
  $("#loyalty-text").textContent = `${loyalty}%`;
  $("#brand-strip").innerHTML = ["Gloregni", "Iusdicta", "Satiae", "Thofestoe", "Miseritae"].map((brand) => `
    <span class="brand" style="color:${colors[brand]}; opacity:${state.activeBrands.includes(brand) ? 1 : 0.35}">${brand.slice(0, 3)}</span>
  `).join("");
  const chapter = chapters[state.chapterIndex] || chapters[0];
  $("#chapter-label").textContent = `${chapter.id} - ${chapter.name} · ${chapter.location}`;
}

function saveGame() {
  localStorage.setItem("aes_save", JSON.stringify({
    profile: state.profile,
    stats: state.stats,
    chapterIndex: state.chapterIndex,
    ore: state.ore,
    crafted: state.crafted,
    activeBrands: state.activeBrands,
  }));
}

function loadSave() {
  try {
    const save = JSON.parse(localStorage.getItem("aes_save") || "null");
    if (!save) return;
    state.profile = { ...state.profile, ...save.profile };
    state.ore = save.ore || 0;
    state.crafted = save.crafted || [];
    state.activeBrands = save.activeBrands || [];
  } catch {
    localStorage.removeItem("aes_save");
  }
}

function clamp(value, min, max) {
  return Math.max(min, Math.min(max, value));
}

loadSave();
initMenus();
bindUi();
setOrder("shield");
