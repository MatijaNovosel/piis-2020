<template>
  <nav class="navbar sticky-top navbar-expand navbar-light navbar-general">
    <span class="navbar-logo"><logo class="mr-3 mb-1" />PIIS 2020 <span class="subtitle-text ml-2">Matija Novosel</span></span>
    <div class="collapse navbar-collapse">
      <ul class="navbar-nav mx-auto">
        <li class="nav-item mr-3">
          <span
            @click="redirect({ name: 'vjezba-1' })"
            class="badge badge-pill pill"
            >Vježba 1</span
          >
        </li>
        <li class="nav-item">
          <span
            @click="redirect({ name: 'vjezba-3' })"
            class="badge badge-pill pill"
            >Vježba 3</span
          >
        </li>
      </ul>
    </div>
  </nav>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import { useRouter } from "vue-router";
import logo from "@/components/logo.vue";

interface Route {
  name: string;
}

export default defineComponent({
  name: "navbar",
  components: {
    logo
  },
  setup() {
    const router = useRouter();

    function redirect(route: Route) {
      router.push({ name: route.name });
    }

    return {
      redirect
    };
  }
});
</script>

<style scoped>
.navbar-general {
  border-bottom: 1px solid var(--border-color-dark);
  height: var(--navbar-height);
  max-height: var(--navbar-height);
  box-shadow: 0px 3px 9px #888888;
}
.navbar-logo {
  position: absolute;
  left: 35px;
  top: 20px;
  font-size: 20px;
  color: #273849;
  font-family: "Dosis", "Source Sans Pro", "Helvetica Neue", Arial, sans-serif;
  font-weight: 500;
}
.subtitle-text {
  color: grey;
  font-size: 12px;
}
.pill {
  font-size: 12px;
  cursor: pointer;
  box-shadow: 5px 5px 4px #888888;
  padding: 6px 12px;
  background-color: #273849;
  color: white;
}
.pill:hover {
  background-color: grey;
}
</style>
